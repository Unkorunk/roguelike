#pragma once

#include <cmath>
#include <cstdint>

class Vec2d {
public:
	Vec2d();
	Vec2d(uint32_t x, uint32_t y);
	Vec2d(const Vec2d& other);

	uint32_t x, y;

	Vec2d operator +(const Vec2d& rhs);
	Vec2d& operator +=(const Vec2d& rhs);

	Vec2d operator -(const Vec2d& rhs);
	Vec2d& operator -=(const Vec2d& rhs);

	uint32_t length();
	static uint32_t distance(const Vec2d& lhs, const Vec2d& rhs);
};
