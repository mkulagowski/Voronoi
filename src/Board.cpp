#include "Board.hpp"
#include "Color.hpp"
#include "../jpeg/jpgd.h"
#include "../jpeg/jpge.h"

Board::Board(uint16_t w, uint16_t h)
	: mWidth(w)
	, mHeight(h)
	, isUsed(false)
	, mData(w * h, Color::getInstance()->getNone())
{
}

Vector Board::get(uint16_t x, uint16_t y)
{
	if (x < mWidth && y < mHeight)
		return mData[mWidth * y + x];

	return Vector();
}

void Board::set(uint16_t x, uint16_t y, Vector val)
{
	if (x < mWidth && y < mHeight)
		mData[mWidth * y + x] = val;
	
	if (!isUsed)
		isUsed = true;
}

Vector Board::get(Point p)
{
	return get(p.x(), p.y());
}

void Board::set(Point p, const Vector& val)
{
	set(p.x(), p.y(), val);
}

bool Board::isEmpty(uint16_t x, uint16_t y)
{
	return x < mWidth && y < mHeight && get(x, y) == Color::getInstance()->getNone();
}

bool Board::isEmpty(Point p)
{
	return isEmpty(p.x(), p.y());
}

int Board::getWidth() const
{
	return mWidth;
}

int Board::getHeight() const
{
	return mHeight;
}

std::unique_ptr<std::vector<uint8_t>> Board::getRawData() const
{
	auto raw = std::make_unique<std::vector<uint8_t>>();
	raw->reserve(mData.size() * 3);
	for (auto i : mData) {
		raw->emplace_back(i[0]);
		raw->emplace_back(i[1]);
		raw->emplace_back(i[2]);
	}

	return raw;
}

void Board::save(std::string path) const
{
	//auto rawData = getRawData();

	jpge::params jpegParams;
	jpegParams.m_quality = 100;
	jpge::compress_image_to_jpeg_file(path.c_str(), getWidth(), getHeight(), 3,
		(uint8_t*)mData.data(), jpegParams);
}

void Board::clear()
{
	if (isUsed)
	{
		mData.clear();
		mData = std::vector<Vector>(mWidth * mHeight, Color::getInstance()->getNone());
	}
}
