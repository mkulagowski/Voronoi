#pragma once
#include <vector>
#include <array>
#include <memory>

class Point;
using PointVect = std::vector<Point>;
using PointVectPtr = std::unique_ptr<PointVect>;
using Point4Arr = std::array<Point, 4>;
using VectPointVect = std::vector<PointVect>;
using VectPointVectPtr = std::unique_ptr<std::vector<PointVectPtr>>;

class Point
{
public:
	Point(uint16_t x, uint16_t y);
	Point(const Point& p);
	uint16_t x() const;
	uint16_t y() const;
	Point4Arr getAround() const;
	bool operator<(const Point& rhs) const;
	bool operator==(const Point& rhs) const;

	static Point minMax(Point p1, Point p2);
	static Point maxMin(Point p1, Point p2);
	static Point max(Point p1, Point p2);
	static Point min(Point p1, Point p2);
private:
	uint16_t mX, mY;
};

#include <functional>
namespace std {
	template <>
	struct std::hash<Point>
	{
		std::size_t operator()(const Point& k) const
		{
			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return (53 + (std::hash<uint16_t>()(k.x()))) * 53 + (std::hash<uint16_t>()(k.y()));
		}
	};

}