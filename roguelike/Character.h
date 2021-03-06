#pragma once

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

	uint32_t getHP() const;
	uint32_t getMaxHP() const;
	uint32_t getDamage() const;
	std::pair<int, int> getAim() const;

	bool isDied() const;

	void setHP(uint32_t hp);
	void setMaxHP(uint32_t max_hp);
	void setDamage(uint32_t damage);
	void setAim(int x, int y);

	void takeDamage(uint32_t damage);

	void loadFromSettings(const std::string& classname) override;

	virtual bool move() = 0;
	virtual bool shoot(std::pair<int, int>& bullet_params) = 0;
private:
	std::function<std::shared_ptr<GameObject>(char sym, const Vec2d & origin)> validator;

	uint32_t hp;
	uint32_t max_hp;
	uint32_t damage;

	std::pair<int, int> aim;
};
