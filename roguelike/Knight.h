#pragma once

#include "Character.h"
#include "Dragon.h"
#include "Bullet.h"
#include "Zombie.h"

class Knight : public Character {
public:
	Knight();
	explicit Knight(const Vec2d& origin);

	bool move() override;

	void collideWith(Zombie& zombie) override;
	void collideWith(Dragon& dragon) override;
	void collideWith(Bullet& bullet) override;

	bool shoot(std::pair<int, int>& bullet_params) override;

	void loadFromSettings(const std::string& classname) override;
private:
	bool is_shoot;
};
