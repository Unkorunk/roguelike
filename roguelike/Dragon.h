#pragma once

#include "Character.h"
#include "Knight.h"

class Dragon : public Character {
public:
	Dragon();
	explicit Dragon(const Vec2d& origin);

	bool move() override;

	void collideWith(Knight& knight) override;
};
