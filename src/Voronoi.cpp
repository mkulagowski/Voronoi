#include "Voronoi.hpp"
#include "Color.hpp"
#include <string>

Voronoi::Voronoi(std::string path, uint16_t width, uint16_t height)
	: mBoard(width, height)
	, mPath(path)
{
}

void Voronoi::calculate(std::shared_ptr<std::vector<Rect>> rects)
{
	calculate(rects, false, true, 0);
}

void Voronoi::calculate(std::shared_ptr<std::vector<Rect>> rects, bool saveGifsFolder, bool saveOutput, uint8_t saveInterval)
{
	mBoard.clear();

	auto wallColor = Color::getInstance()->getWall();
	auto borderPts = initializeWalls(rects, wallColor);

	std::unique_ptr<std::set<Point>> lines = paintBorders(std::move(borderPts));

	// if given path was to the file, not dir, try to survive somehow
	if (mPath.rfind('.') != std::string::npos)
	{
		int last1 = mPath.rfind('/');
		int last2 = mPath.rfind('\\');
		last1 = last1 != std::string::npos ? last1 : -1;
		last2 = last2 != std::string::npos ? last2 : -1;
		mPath.erase(last1 < last2 ? last2 : last1);
	}
	std::string basePath = mPath + "\\";
	std::unordered_map<Point, Vector> entryMap; //< needed to see where 2 colors colide
	std::set<Point> newLines;
	uint16_t counter = 0;

	// go until all fields get processed
	while (!lines->empty()) {
		for (auto i : *lines.get()) {
			if (mBoard.get(i) != wallColor) {
				for (const auto& a : i.getAround())
				{
					if (mBoard.isEmpty(a) && mBoard.get(a) != wallColor)
					{
						auto idx = entryMap.find(a);
						auto currColor = mBoard.get(i);

						if (idx != entryMap.end())
							entryMap[a] = idx->second == currColor ? currColor : wallColor;
						else
							entryMap[a] = currColor;

						newLines.insert(a);
					}
				}
			}
		}

		for (const auto& i : entryMap)
			mBoard.set(i.first, i.second);

		entryMap.clear();
		lines->clear();
		lines->swap(newLines);

		if (saveGifsFolder && ++counter % saveInterval == 0)
			mBoard.save(basePath + std::to_string(counter) + ".jpeg");
	}

	if (saveOutput)
		mBoard.save(basePath + "output123.jpg");
}

std::unique_ptr<std::vector<PointVectPtr>> Voronoi::initializeWalls(std::shared_ptr<std::vector<Rect>> obstacles, Vector wallColor)
{
	auto borderPts = std::make_unique<std::vector<PointVectPtr>>();
	PointVectPtr pts = std::make_unique<PointVect>();
	PointVectPtr pts2 = std::make_unique<PointVect>();
	int w = mBoard.getWidth();
	int h = mBoard.getHeight();
	for (int i = 0; i < w; i++)
	{
		pts->emplace_back(i, 0);
		pts2->emplace_back(i, h - 1);
	}
	borderPts->push_back(std::move(pts));
	borderPts->push_back(std::move(pts2));
	pts = std::make_unique<PointVect>();
	pts2 = std::make_unique<PointVect>();
	for (int i = 0; i < h; i++)
	{
		pts->emplace_back(0, i);
		pts2->emplace_back(w - 1, i);
	}

	borderPts->push_back(std::move(pts));
	borderPts->push_back(std::move(pts2));
	for (const auto& i : *obstacles.get())
	{
		auto t = i.getLines();
		for (const auto& j : *t)
			mBoard.set(j, wallColor);

		auto b = i.getBorder();
		for (auto& j : *b)
			borderPts->push_back(std::move(j));
	}

	return std::move(borderPts);
}

std::unique_ptr<std::set<Point>> Voronoi::paintBorders(std::unique_ptr<std::vector<PointVectPtr>> borderPts)
{
	auto lines = std::make_unique<std::set<Point>>();
	// get the color iterator, to go through all available colors
	auto colIt = Color::getInstance()->cbegin();
	for (uint16_t i = 0; i < borderPts->size(); ++i)
	{
		Vector color = colIt->second;
		auto border = (*borderPts)[i].get();
		for (const auto& p : *border)
		{
			if (mBoard.isEmpty(p))
			{
				mBoard.set(p, color);
				lines->insert(p);
			}
		}

		// if we run out of colors, reuse the old ones and hope for the best...
		if (++colIt == Color::getInstance()->cend())
			colIt = Color::getInstance()->cbegin();
	}

	return std::move(lines);
}
