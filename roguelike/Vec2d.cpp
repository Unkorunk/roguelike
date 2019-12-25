#include "Vec2d.h"

Vec2d::Vec2d() : x(), y() {
}

Vec2d::Vec2d(size_t x, size_t y) : x(x), y(y) {
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

bool Vec2d::operator==(const Vec2d& rhs) {
	return (this->x == rhs.x && this->y == rhs.y);
}

bool Vec2d::operator!=(const Vec2d& rhs) {
	return !this->operator==(rhs);
}

size_t Vec2d::length() {
	return this->x + this->y;
}

size_t Vec2d::distance(const Vec2d& lhs, const Vec2d& rhs) {
	size_t dist = 0;
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
