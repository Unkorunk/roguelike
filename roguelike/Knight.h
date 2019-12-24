#pragma once

#include "Character.h"
#include "Dragon.h"
#include "Zombie.h"

class Knight : public Character {
public:
	Knight();
	explicit Knight(const Vec2d& origin);

	bool move() override;

	void collideWith(Zombie& zombie) override;
	void collideWith(Dragon& dragon) override;
};
