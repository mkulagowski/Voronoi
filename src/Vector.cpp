#include "Vector.hpp"

Vector::Vector(uint8_t x, uint8_t y, uint8_t z)
	: mVal{x, y, z}
{}

Vector::Vector(uint8_t x)
	: Vector(x, x, x)
{}

Vector::Vector()
	: Vector(0)
{}


Vector Vector::avg(const Vector & o) const
{
	uint16_t x = ((uint16_t)mVal[0] + o[0]) / 2;
	uint16_t y = ((uint16_t)mVal[1] + o[1]) / 2;
	uint16_t z = ((uint16_t)mVal[2] + o[2]) / 2;
	return Vector(x, y, z);
}

uint8_t Vector::operator[] (uint8_t index) const
{
	if (index < 3)
		return mVal[index];

	return 0;
}

bool Vector::operator== (const Vector& b) const
{
	return mVal[0] == b.mVal[0]
		&& mVal[1] == b.mVal[1]
		&& mVal[2] == b.mVal[2];
}

bool Vector::operator!= (const Vector& b) const
{
	return !(*this == b);
}