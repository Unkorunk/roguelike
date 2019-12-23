#pragma once

#include "Character.h"

class Bullet : public Character {
public:
	Bullet();
	Bullet(const Vec2d& origin);
	Bullet(const Vec2d& origin, const Vec2d& aim);

	bool move() override;
	bool shoot(Vec2d& bullet_params) override {
		return false;
	}
private:
	Vec2d aim;
};

