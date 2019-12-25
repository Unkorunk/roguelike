#pragma once

#include <cmath>
#include <cstdint>

class Vec2d {
public:
	Vec2d();
	Vec2d(size_t x, size_t y);
	Vec2d(const Vec2d& other);

	size_t x, y;

	Vec2d operator +(const Vec2d& rhs);
	Vec2d& operator +=(const Vec2d& rhs);

	Vec2d operator -(const Vec2d& rhs);
	Vec2d& operator -=(const Vec2d& rhs);

	bool operator ==(const Vec2d& rhs);
	bool operator !=(const Vec2d& rhs);

	size_t length();
	static size_t distance(const Vec2d& lhs, const Vec2d& rhs);
};
