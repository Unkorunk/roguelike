#pragma once

#include "Character.h"

class Zombie : public Character {
public:
	Zombie();
	explicit Zombie(const Vec2d& origin);

	bool move() override;
};

