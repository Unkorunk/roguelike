#include "GameObject.h"

GameObject::GameObject() : sym(), origin() {
}

GameObject::GameObject(char sym) : sym(sym), origin() {
}

GameObject::GameObject(char sym, const Vec2d& origin) : sym(sym), origin(origin) {
}

GameObject::~GameObject() {
}

void GameObject::setOrigin(const Vec2d& origin) {
	this->origin = origin;
}

void GameObject::setOrigin(int32_t x, int32_t y) {
	this->origin.x = x;
	this->origin.y = y;
}

Vec2d GameObject::getOrigin() {
	return this->origin;
}

char GameObject::getSym() {
	return this->sym;
}
