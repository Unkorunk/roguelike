#include "Bullet.h"

Bullet::Bullet() : Character('*') {
	this->aim = Vec2d(1, 0);
}

Bullet::Bullet(const Vec2d& origin) : Character('*', origin) {
	this->aim = Vec2d(1, 0);
}

Bullet::Bullet(const Vec2d& origin, const Vec2d& aim) : Character('*', origin) {
	this->aim = aim;
}

bool Bullet::move() {
	if (this->getValidator()(this->getSym(), this->getOrigin())) {
		this->setHP(0);
		return false;
	}

	Vec2d next_origin = this->getOrigin() + this->aim;

	if (this->getValidator()(this->getSym(), next_origin)) {
		this->setOrigin(next_origin);
		return true;
	}

	this->setHP(0);

	return false;
}
