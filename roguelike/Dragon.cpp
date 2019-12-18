#include "Dragon.h"

Dragon::Dragon() : Character('D') {
	this->setDamage(8);
	this->setMaxHP(50);
	this->setHP(50);
}

Dragon::Dragon(const Vec2d& origin) : Character('D', origin) {
	this->setDamage(8);
	this->setMaxHP(50);
	this->setHP(50);
}

bool Dragon::move() {
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
