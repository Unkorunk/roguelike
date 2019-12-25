#include "AidKit.h"

AidKit::AidKit(const Vec2d& origin) : GameObject('+', origin), how_many(30) {
}

AidKit::AidKit(const Vec2d& origin, uint32_t how_many) : GameObject('+', origin), how_many(how_many) {
}

void AidKit::collideWith(Knight& knight) {
	this->remove();
	knight.setHP(knight.getHP() + this->how_many);
	this->how_many = 0;
}
