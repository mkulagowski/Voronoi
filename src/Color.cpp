#include "Color.hpp"

Color::Color()
	: mIsInitialized(false)
	, mNone(Vector(0))
	, mWall(Vector(1))
{
}

Color* Color::getInstance()
{
	static Color mInstance;
	if (!mInstance.mIsInitialized)
		mInstance.init();

	return &mInstance;
}

void Color::init()
{
	mColorMap = std::unordered_map<std::string, Vector>{
		{ "RED", Vector(255, 0, 0) },
		{ "LIME", Vector(0, 255, 0) },
		{ "BLUE", Vector(0, 0, 255) },
		{ "YELLOW", Vector(255, 255, 0) },
		{ "ORANGE", Vector(255, 69, 0) },
		{ "MAGENTA", Vector(255, 0, 255) },
		{ "CYAN", Vector(0, 255, 255) },
		{ "SALMON", Vector(250, 128, 114) },
		{ "GREEN", Vector(0, 128, 0) },
		{ "MAROON", Vector(128, 0, 0) },
		{ "PINK", Vector(255, 105, 180) },
		{ "SKYBLUE", Vector(0, 191, 255) },
		{ "TURQUOISE", Vector(64, 224, 208) },
		{ "KHAKI", Vector(240, 230, 140) },
		{ "GOLD", Vector(218, 165, 32) },
		{ "STEEL", Vector(176, 196, 222) }
	};
	mIsInitialized = true;
}

const Vector& Color::operator[] (std::string name) const
{
	return get(name);
}

const Vector& Color::get(std::string name) const
{
	auto idx = mColorMap.find(name);
	if (idx != mColorMap.end())
		return idx->second;

	return Vector();
}

const Vector& Color::getNone() const
{
	return mNone;
}

const Vector& Color::getWall() const
{
	return mWall;
}

std::unordered_map<std::string, Vector>::const_iterator Color::cbegin() const
{
	return mColorMap.cbegin();
}

std::unordered_map<std::string, Vector>::const_iterator Color::cend() const
{
	return mColorMap.cend();
}