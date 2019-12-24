#pragma once

#include "Character.h"

#include "Knight.h"

class Zombie : public Character {
public:
	Zombie();
	explicit Zombie(const Vec2d& origin);

	bool move() override;

	void collideWith(Knight& knight) override;
};

