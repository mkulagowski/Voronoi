#include "Point.hpp"

Point::Point(uint16_t x, uint16_t y)
	: mX(x)
	, mY(y)
{
}

Point::Point(const Point& p)
	: Point(p.x(), p.y())
{
}

uint16_t Point::x() const
{
	return mX;
}

uint16_t Point::y() const
{
	return mY;
}

Point Point::minMax(Point p1, Point p2)
{
	uint16_t x = p1.x() < p2.x() ? p1.x() : p2.x();
	uint16_t y = p1.y() > p2.y() ? p1.y() : p2.y();
	return Point(x, y);
}

Point Point::maxMin(Point p1, Point p2)
{
	uint16_t x = p1.x() > p2.x() ? p1.x() : p2.x();
	uint16_t y = p1.y() < p2.y() ? p1.y() : p2.y();
	return Point(x, y);
}

Point Point::max(Point p1, Point p2)
{
	uint16_t x = p1.x() > p2.x() ? p1.x() : p2.x();
	uint16_t y = p1.y() > p2.y() ? p1.y() : p2.y();
	return Point(x, y);
}

Point Point::min(Point p1, Point p2)
{
	uint16_t x = p1.x() < p2.x() ? p1.x() : p2.x();
	uint16_t y = p1.y() < p2.y() ? p1.y() : p2.y();
	return Point(x, y);
}

Point4Arr Point::getAround() const
{
	return Point4Arr{ {
		Point(mX    , mY - 1),
		Point(mX    , mY + 1),
		Point(mX - 1, mY),
		Point(mX + 1, mY),
		/*
		Point(mX + 1, mY - 1),
		Point(mX + 1, mY + 1),
		Point(mX - 1, mY - 1),
		Point(mX - 1, mY + 1)
		*/
	} };
}

bool Point::operator< (const Point& b) const
{
	uint32_t b1 = mX;
	b1 = (b1 << 16) | mY;
	uint32_t b2 = b.mX;
	b2 = (b2 << 16) | b.mY;

	return b1 < b2;
}

bool Point::operator== (const Point& b) const
{
	uint32_t b1 = mX;
	b1 = (b1 << 16) | mY;
	uint32_t b2 = b.mX;
	b2 = (b2 << 16) | b.mY;

	return b1 == b2;
	/*
	auto b1 = mX == b.mX;
	auto b2 = mY == b.mY;
	return b1 && b2;
	*/
}
