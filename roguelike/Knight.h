#pragma once

#include "Character.h"

class Knight : public Character {
public:
	Knight();
	explicit Knight(const Vec2d& origin);

	bool move() override;
};
