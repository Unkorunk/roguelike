#pragma once

#include "GameObject.h"

class Wall : public GameObject {
public:
	Wall();
	explicit Wall(const Vec2d& origin);
};
