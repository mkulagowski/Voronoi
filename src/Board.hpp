#include "Vector.hpp"
#include "Point.hpp"
#include <vector>
class Board {
public:
	Board(uint16_t w, uint16_t h);

	Vector get(uint16_t x, uint16_t y);
	Vector get(Point p);

	void set(uint16_t x, uint16_t y, Vector val);
	void set(Point p, const Vector& val);

	bool isEmpty(uint16_t x, uint16_t y);
	bool isEmpty(Point p);

	int getWidth() const;
	int getHeight() const;

	void save(std::string path) const;
	void clear();

	std::unique_ptr<std::vector<uint8_t>> getRawData() const;

private:
	uint16_t mWidth, mHeight;
	std::vector<Vector> mData;
	bool isUsed;
};