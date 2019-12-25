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
	switch (rand() % 100) {
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

void Zombie::collideWith(Knight& knight) {
	this->takeDamage(knight.getDamage());
}

void Zombie::collideWith(Bullet& bullet) {
	this->takeDamage(bullet.getDamage());
	bullet.setHP(0);
}

bool Zombie::shoot(Vec2d& bullet_params) {
	bullet_params = this->getAim();
	return (rand() % 15 == 0);
}
