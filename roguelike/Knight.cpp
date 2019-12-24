#include "Knight.h"

Knight::Knight() : Character('K') {
	this->setDamage(10);
	this->setMaxHP(100);
	this->setHP(100);
}

Knight::Knight(const Vec2d& origin) : Character('K', origin) {
	this->setDamage(10);
	this->setMaxHP(100);
	this->setHP(100);
}

bool Knight::move() {
	Vec2d next_origin = this->getOrigin();
	int ch;
	if ((ch = getch()) > 0) {
		if (ch == 'w') {
			next_origin.y--;
		} else if (ch == 'a') {
			next_origin.x--;
		} else if (ch == 'd') {
			next_origin.x++;
		} else if (ch == 's') {
			next_origin.y++;
		}
	}
	
	while ((ch = getch()) > 0) {} // clear queue

	auto collision_obj = this->getValidator()(this->getSym(), next_origin);

	if (collision_obj) {
		collision_obj->collideWith(*this);
	} else {
		this->setOrigin(next_origin);
		return true;
	}

	return false;
}

void Knight::collideWith(Zombie& zombie) {
	this->takeDamage(zombie.getDamage());
}

void Knight::collideWith(Dragon& dragon) {
	this->takeDamage(dragon.getDamage());
}
