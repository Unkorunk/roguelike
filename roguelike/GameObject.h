#pragma once

#include <curses.h>

#include "Vec2d.h"
#include "Settings.h"

class Knight;
class Princess;
class Wall;
class Dragon;
class Zombie;
class Bullet;

class GameObject {
public:
	GameObject();
	explicit GameObject(char sym);
	explicit GameObject(char sym, const Vec2d& origin);
	virtual ~GameObject() = default;

	void setOrigin(const Vec2d& origin);
	void setOrigin(size_t x, size_t y);

	Vec2d getOrigin();
	char getSym();

	void remove() {
		if (!deleted) {
			::move(static_cast<int>(this->getOrigin().y), static_cast<int>(this->getOrigin().x));
			::addch(' ');
			deleted = true;
		}
	}
	bool getRemoved() const {
		return deleted;
	}

	virtual void loadFromSettings(const std::string& classname) {}

	virtual void collideWith(Knight& knight) {}
	virtual void collideWith(Princess& princess) {}
	virtual void collideWith(Wall& wall) {}
	virtual void collideWith(Dragon& dragon) {}
	virtual void collideWith(Zombie& zombie) {}
	virtual void collideWith(Bullet& zombie) {}
private:
	Vec2d origin;
	char sym;

	bool deleted;
};
