#pragma once
#include <cstdint>


class Vector {
public:
	Vector();
	Vector(uint8_t x, uint8_t y, uint8_t z);
	Vector(uint8_t x);

	Vector avg(const Vector& other) const;
	uint8_t operator[] (uint8_t index) const;
	bool operator== (const Vector& b) const;
	bool operator!= (const Vector& b) const;
private:
	uint8_t mVal[3];
};