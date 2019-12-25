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
	switch (rand() % 10) {
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

	auto collision_obj = this->getValidator()(this->getSym(), next_origin);
	if (collision_obj) {
		collision_obj->collideWith(*this);
		auto bullet = std::dynamic_pointer_cast<Bullet>(collision_obj);
		if (bullet) {
			bullet->remove();
			this->setOrigin(next_origin);
			return true;
		}
	} else {
		this->setOrigin(next_origin);
		return true;
	}

	return false;
}

void Dragon::collideWith(Knight& knight) {
	this->takeDamage(knight.getDamage());
}

void Dragon::collideWith(Bullet& bullet) {
	this->takeDamage(bullet.getDamage());
	bullet.setHP(0);
}

bool Dragon::shoot(Vec2d& bullet_params) {
	bullet_params = this->getAim();
	return (rand() % 15 == 0);
}
