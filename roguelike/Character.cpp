#include "Character.h"

Character::Character(char sym) : GameObject(sym) {
	this->validator = [](char sym, const Vec2d& origin) {
		return std::shared_ptr<GameObject>();
	};
	this->hp = this->max_hp = 100;
	this->damage = 0;
	this->deleted = false;
	this->aim = Vec2d(1, 0);
}

Character::Character(char sym, const Vec2d& origin) : GameObject(sym, origin) {
	this->validator = [](char sym, const Vec2d& origin) {
		return std::shared_ptr<GameObject>();
	};
	this->hp = this->max_hp = 100;
	this->damage = 0;
	this->deleted = false;
	this->aim = Vec2d(1, 0);
}

void Character::setValidator(const std::function<std::shared_ptr<GameObject>(char sym, const Vec2d & origin)>& validator) {
	this->validator = validator;
}

const std::function<std::shared_ptr<GameObject>(char sym, const Vec2d & origin)>& Character::getValidator() {
	return this->validator;
}

uint32_t Character::getHP() const {
	return this->hp;
}

uint32_t Character::getMaxHP() const {
	return this->max_hp;
}

uint32_t Character::getDamage() const {
	if (this->hp == 0) {
		return 0;
	}
	return this->damage;
}

Vec2d Character::getAim() const {
	return aim;
}

bool Character::isDied() const {
	return (this->hp == 0);
}

void Character::setHP(uint32_t hp) {
	if (hp > this->max_hp) {
		this->hp = this->max_hp;
	} else {
		this->hp = hp;
	}
}

void Character::setMaxHP(uint32_t max_hp) {
	this->max_hp = max_hp;
	if (this->hp > this->max_hp) {
		this->hp = this->max_hp;
	}
}

void Character::setDamage(uint32_t damage) {
	this->damage = damage;
}

void Character::setAim(Vec2d aim) {
	this->aim = aim;
}

void Character::takeDamage(uint32_t damage) {
	if (damage > this->hp) {
		this->hp = 0;
	} else {
		this->hp -= damage;
	}
}
