#include "Bullet.h"

Bullet::Bullet() : Character('*') {
	this->aim = Vec2d(1, 0);
	this->setDamage(0);
	this->setMaxHP(10000);
	this->setHP(10000);
}

Bullet::Bullet(const Vec2d& origin) : Character('*', origin) {
	this->aim = Vec2d(1, 0);
	this->setDamage(0);
	this->setMaxHP(10000);
	this->setHP(10000);
}

Bullet::Bullet(const Vec2d& origin, const Vec2d& aim) : Character('*', origin) {
	this->aim = aim;
}

bool Bullet::move() {
	Vec2d next_origin = this->getOrigin() + this->aim;

	auto collision_obj = this->getValidator()(this->getSym(), next_origin);
	if (collision_obj) {
		collision_obj->collideWith(*this);
	} else {
		this->setOrigin(next_origin);
		return true;
	}

	this->setHP(0);

	return false;
}

void Bullet::collideWith(Knight& knight) {
	if (!this->isDied()) {
		knight.takeDamage(this->getDamage());
		this->setHP(0);
	}
}

void Bullet::collideWith(Zombie& zombie) {
	if (!this->isDied()) {
		zombie.takeDamage(this->getDamage());
		this->setHP(0);
	}
}

void Bullet::collideWith(Dragon& dragon) {
	if (!this->isDied()) {
		dragon.takeDamage(this->getDamage());
		this->setHP(0);
	}
}
