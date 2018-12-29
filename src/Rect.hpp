#pragma once
#include "Point.hpp"
#include <vector>
class Rect
{
public:
	Rect(Point p1, Point p2);

	PointVectPtr getLines() const;
	PointVectPtr getLines2() const;
	PointVectPtr getTop() const;
	PointVectPtr getBottom() const;
	PointVectPtr getLeft() const;
	PointVectPtr getRight() const;

	VectPointVectPtr getBorder() const;

private:
	Point mTL, mTR, mBL, mBR;
};