#pragma once

#include <curses.h>
#include "GameObject.h"
#include <cstdint>
#include <curses.h>
#include <functional>
#include <memory>

class Character : public GameObject {
public:
	Character() = delete;
	explicit Character(char sym);
	Character(char sym, const Vec2d& origin);

	void setValidator(const std::function<std::shared_ptr<GameObject>(char sym, const Vec2d & origin)>& validator);
	const std::function<std::shared_ptr<GameObject>(char sym, const Vec2d & origin)>& getValidator();

	uint32_t getHP();
	uint32_t getMaxHP();
	uint32_t getDamage();

	bool isDied();

	void remove() {
		if (!deleted) {
			::move(this->getOrigin().y, this->getOrigin().x);
			::addch(' ');
			deleted = true;
		}
	}

	void setHP(uint32_t hp);
	void setMaxHP(uint32_t max_hp);
	void setDamage(uint32_t damage);

	void takeDamage(uint32_t damage);

	virtual bool move() = 0;
private:
	std::function<std::shared_ptr<GameObject>(char sym, const Vec2d & origin)> validator;

	uint32_t hp;
	uint32_t max_hp;
	uint32_t damage;

	bool deleted;
};
