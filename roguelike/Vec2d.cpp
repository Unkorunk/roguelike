#include "Vec2d.h"

Vec2d::Vec2d() : x(), y() {
}

Vec2d::Vec2d(uint32_t x, uint32_t y) : x(x), y(y) {
}

Vec2d::Vec2d(const Vec2d& other) : x(other.x), y(other.y) {
}

Vec2d Vec2d::operator+(const Vec2d& rhs) {
	return Vec2d(this->x + rhs.x, this->y + rhs.y);
}

Vec2d& Vec2d::operator+=(const Vec2d& rhs) {
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

Vec2d Vec2d::operator-(const Vec2d& rhs) {
	return Vec2d(this->x - rhs.x, this->y - rhs.y);
}

Vec2d& Vec2d::operator-=(const Vec2d& rhs) {
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

uint32_t Vec2d::length() {
	return this->x + this->y;
}

uint32_t Vec2d::distance(const Vec2d& lhs, const Vec2d& rhs) {
	uint32_t dist = 0;
	if (lhs.x > rhs.x) {
		dist += lhs.x - rhs.x;
	} else {
		dist += rhs.x - lhs.x;
	}

	if (lhs.y > rhs.y) {
		dist += lhs.y - rhs.y;
	} else {
		dist += rhs.y - lhs.y;
	}

	return dist;
}
