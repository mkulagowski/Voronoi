#pragma once
#include "Rect.hpp"
#include "Board.hpp"
#include "Point.hpp"
#include <set>

class Voronoi
{
public:
	Voronoi(std::string path, uint16_t width, uint16_t height);

	void calculate(std::shared_ptr<std::vector<Rect>> rects);
	void calculate(std::shared_ptr<std::vector<Rect>> rects, bool saveGifsFolder, bool saveOutput, uint8_t saveInterval);

private:
	std::unique_ptr<std::vector<PointVectPtr>> initializeWalls(std::shared_ptr<std::vector<Rect>> obstacles, Vector wallColor);
	std::unique_ptr<std::set<Point>> paintBorders(std::unique_ptr<std::vector<PointVectPtr>> borderPts);

	Board mBoard;
	std::string mPath;
};