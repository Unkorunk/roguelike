#pragma once

#include "GameObject.h"
#include <cstdint>
#include <curses.h>
#include <functional>

class Character : public GameObject {
public:
	Character() = delete;
	explicit Character(char sym);
	Character(char sym, const Vec2d& origin);

	void setValidator(const std::function<bool(char sym, const Vec2d & origin)>& validator);
	const std::function<bool(char sym, const Vec2d & origin)>& getValidator();

	uint32_t getHP();
	uint32_t getMaxHP();
	uint32_t getDamage();

	bool isDied();

	void setHP(uint32_t hp);
	void setMaxHP(uint32_t max_hp);
	void setDamage(uint32_t damage);

	void takeDamage(uint32_t damage);

	virtual bool move() = 0;
private:
	std::function<bool(char sym, const Vec2d & origin)> validator;

	uint32_t hp;
	uint32_t max_hp;
	uint32_t damage;
};
