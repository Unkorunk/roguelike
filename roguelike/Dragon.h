#pragma once

#include "Character.h"

#include "Knight.h"
#include "Bullet.h"

class Dragon : public Character {
public:
	Dragon();
	explicit Dragon(const Vec2d& origin);

	bool move() override;

	void collideWith(Knight& knight) override;
	void collideWith(Bullet& bullet) override;

	bool shoot(Vec2d& bullet_params) override;
};
