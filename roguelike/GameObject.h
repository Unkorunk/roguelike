#pragma once

#include "Vec2d.h"

class Knight;
class Princess;
class Wall;
class Dragon;
class Zombie;

class GameObject {
public:
	GameObject();
	explicit GameObject(char sym);
	explicit GameObject(char sym, const Vec2d& origin);
	virtual ~GameObject();

	void setOrigin(const Vec2d& origin);
	void setOrigin(size_t x, size_t y);

	Vec2d getOrigin();
	char getSym();

	virtual void collideWith(GameObject& gameObject) {}
	virtual void collideWith(Knight& knight) {}
	virtual void collideWith(Princess& princess) {}
	virtual void collideWith(Wall& wall) {}
	virtual void collideWith(Dragon& dragon) {}
	virtual void collideWith(Zombie& zombie) {}
private:
	Vec2d origin;
	char sym;
};
