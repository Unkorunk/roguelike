#include "GameObject.h"

GameObject::GameObject() : sym(), origin(), deleted(false) {
}

GameObject::GameObject(char sym) : sym(sym), origin(), deleted(false) {
}

GameObject::GameObject(char sym, const Vec2d& origin) : sym(sym), origin(origin), deleted(false) {
}

void GameObject::setOrigin(const Vec2d& origin) {
	this->origin = origin;
}

void GameObject::setOrigin(size_t x, size_t y) {
	this->origin.x = x;
	this->origin.y = y;
}

Vec2d GameObject::getOrigin() {
	return this->origin;
}

char GameObject::getSym() {
	return this->sym;
}
