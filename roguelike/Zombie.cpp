#include "Zombie.h"

Zombie::Zombie() : Character('Z') {
	this->setDamage(3);
	this->setMaxHP(30);
	this->setHP(30);
}

Zombie::Zombie(const Vec2d& origin) : Character('Z', origin) {
	this->setDamage(3);
	this->setMaxHP(30);
	this->setHP(30);
}


bool Zombie::move() {
	Vec2d next_origin = this->getOrigin();
	switch (rand() % 5) {
	case 0:
		next_origin.x--;
		break;
	case 1:
		next_origin.x++;
		break;
	case 2:
		next_origin.y--;
		break;
	case 3:
		next_origin.y++;
		break;
	default:
		break;
	}

	if (this->getValidator()(this->getSym(), next_origin)) {
		this->setOrigin(next_origin);
		return true;
	}

	return false;
}
