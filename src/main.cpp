#include "Rect.hpp"
#include "Voronoi.hpp"

int main()
{
	int s = 128;
	Rect r1(Point(7 * s, 2 * s), Point(8 * s, 6 * s));
	Rect r2(Point(14 * s, 0), Point(15 * s, 2 * s));
	Rect r3(Point(13 * s, 8 * s - 1), Point(14 * s, 6 * s));

	auto rects = std::make_shared<std::vector<Rect>, std::initializer_list<Rect>>({r1, r2, r3});
	Voronoi vor("E:\\test", 20 * s, 8 * s);
	vor.calculate(rects, true, true, 10);
}