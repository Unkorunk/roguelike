#pragma once

#include "Character.h"

class Dragon : public Character {
public:
	Dragon();
	explicit Dragon(const Vec2d& origin);

	bool move() override;
};
