#include "Wall.h"

Wall::Wall() : GameObject('#') {
}

Wall::Wall(const Vec2d& origin) : GameObject('#', origin) {
}
