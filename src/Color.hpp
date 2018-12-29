#pragma once
#include "Vector.hpp"
#include <unordered_map>
#include<vector>

class Color {
public:
	static Color* getInstance();
	const Vector& operator[] (std::string name) const;
	const Vector& get(std::string name) const;
	const Vector& getNone() const;
	const Vector& getWall() const;
	std::unordered_map<std::string, Vector>::const_iterator cbegin() const;
	std::unordered_map<std::string, Vector>::const_iterator cend() const;

private:
	Color();
	void init();

	bool mIsInitialized;
	const Vector mNone, mWall;
	std::unordered_map<std::string, Vector> mColorMap;
};