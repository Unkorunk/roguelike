#include "GameObject.h"

GameObject::GameObject() : origin(), sym(), deleted(false) {
}

GameObject::GameObject(char sym) : origin(), sym(sym), deleted(false) {
}

GameObject::GameObject(char sym, const Vec2d& origin) : origin(origin), sym(sym), deleted(false) {
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
