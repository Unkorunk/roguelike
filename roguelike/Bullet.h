#pragma once

#include "Character.h"

#include "Knight.h"
#include "Zombie.h"
#include "Dragon.h"

class Bullet : public Character {
public:
	Bullet();
	Bullet(const Vec2d& origin);
	Bullet(const Vec2d& origin, const Vec2d& aim);

	bool move() override;
	bool shoot(Vec2d& bullet_params) override {
		return false;
	}

	void collideWith(Knight& knight) override;
	void collideWith(Zombie& zombie) override;
	void collideWith(Dragon& dragon) override;
private:
	Vec2d aim;
};

