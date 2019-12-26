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

	bool shoot(std::pair<int, int>& bullet_params) override;

	void loadFromSettings(const std::string& classname) override;
};
