#pragma once

#include "Character.h"

#include "Knight.h"
#include "Bullet.h"

class Zombie : public Character {
public:
	Zombie();
	explicit Zombie(const Vec2d& origin);

	bool move() override;

	void collideWith(Knight& knight) override;
	void collideWith(Bullet& bullet) override;

	bool shoot(std::pair<int, int>& bullet_params) override;

	void loadFromSettings(const std::string& classname) override;
};
