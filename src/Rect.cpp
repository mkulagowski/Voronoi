#include "Rect.hpp"
#include <math.h>

Rect::Rect(Point p1, Point p2)
	: mTL(Point::minMax(p1, p2))
	, mTR(Point::max(p1, p2))
	, mBL(Point::min(p1, p2))
	, mBR(Point::maxMin(p1, p2))
{}

PointVectPtr Rect::getLines() const
{
	PointVectPtr lines = std::make_unique<PointVect>();
	for (int i = mTL.x(); i <= mTR.x(); ++i)
	{
		lines->emplace_back(i, mTL.y());
		lines->emplace_back(i, mBL.y());
	}

	for (int i = mBL.y(); i <= mTL.y(); ++i)
	{
		lines->emplace_back(mTL.x(), i);
		lines->emplace_back(mTR.x(), i);
	}

	return std::move(lines);
}

PointVectPtr Rect::getLines2() const
{
	PointVectPtr lines = std::make_unique<PointVect>();
	for (int i = mTL.x()+1; i <= mTR.x(); ++i)
	{
		lines->emplace_back(i, mTL.y()+1);
		lines->emplace_back(i, mBL.y()-1);
	}

	for (int i = mBL.y() + 1; i <= mTL.y(); ++i)
	{
		lines->emplace_back(mTL.x() - 1, i);
		lines->emplace_back(mTR.x() + 1, i);
	}

	return std::move(lines);
}

PointVectPtr Rect::getTop() const
{
	PointVectPtr lines = std::make_unique<PointVect>();
	for (int i = mTL.x()+1; i < mTR.x(); ++i)
	{
		lines->emplace_back(i, mTL.y() + 1);
	}

	return std::move(lines);
}

PointVectPtr Rect::getBottom() const
{
	PointVectPtr lines = std::make_unique<PointVect>();
	for (int i = mBL.x() + 1; i < mBR.x(); ++i)
	{
		lines->emplace_back(i, mBL.y() - 1);
	}

	return std::move(lines);
}

PointVectPtr Rect::getLeft() const
{
	PointVectPtr lines = std::make_unique<PointVect>();
	for (int i = mBL.y() + 1; i < mTL.y(); ++i)
	{
		lines->emplace_back(mBL.x() - 1, i);
	}

	return std::move(lines);
}

PointVectPtr Rect::getRight() const
{
	PointVectPtr lines = std::make_unique<PointVect>();
	for (int i = mBR.y() + 1; i < mTR.y(); ++i)
	{
		lines->emplace_back(mBR.x() + 1, i);
	}

	return std::move(lines);
}

VectPointVectPtr Rect::getBorder() const
{
	auto retPtr = std::make_unique<std::vector<PointVectPtr>>();
	retPtr->push_back(getLines2());

	return std::move(retPtr);
}