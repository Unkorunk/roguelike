#include "Knight.h"

Knight::Knight() : Character('K') {
	this->setDamage(10);
	this->setMaxHP(100);
	this->setHP(100);
	this->is_shoot = false;

	this->loadFromSettings(std::string() + 'K');
}

Knight::Knight(const Vec2d& origin) : Character('K', origin) {
	this->setDamage(10);
	this->setMaxHP(100);
	this->setHP(100);
	this->is_shoot = false;

	this->loadFromSettings(std::string() + 'K');
}

bool Knight::move() {
	is_shoot = false;
	Vec2d next_origin = this->getOrigin();
	int ch;
	if ((ch = getch()) > 0) {
		if (ch == 'w' || ch == KEY_UP) {
			next_origin.y--;
		} else if (ch == 'a' || ch == KEY_LEFT) {
			next_origin.x--;
		} else if (ch == 'd' || ch == KEY_RIGHT) {
			next_origin.x++;
		} else if (ch == 's' || ch == KEY_DOWN) {
			next_origin.y++;
		} else if (ch == ' ') {
			is_shoot = true;
		}
	}
	
	while ((ch = getch()) > 0) {
		if (ch == ' ') {
			is_shoot = true;
		}
	} // clear queue

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

void Knight::collideWith(Zombie& zombie) {
	this->takeDamage(zombie.getDamage());
}

void Knight::collideWith(Dragon& dragon) {
	this->takeDamage(dragon.getDamage());
}

void Knight::collideWith(Bullet& bullet) {
	this->takeDamage(bullet.getDamage());
	bullet.setHP(0);
}

bool Knight::shoot(Vec2d& bullet_params) {
	bullet_params = this->getAim();
	return is_shoot;
}

void Knight::loadFromSettings(const std::string& classname) {
	Character::loadFromSettings(classname);
}
