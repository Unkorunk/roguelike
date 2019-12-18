#pragma once

#include "Vec2d.h"

class GameObject {
public:
	GameObject();
	explicit GameObject(char sym);
	explicit GameObject(char sym, const Vec2d& origin);
	virtual ~GameObject();

	void setOrigin(const Vec2d& origin);
	void setOrigin(int32_t x, int32_t y);

	Vec2d getOrigin();
	char getSym();
private:
	Vec2d origin;
	char sym;
};
