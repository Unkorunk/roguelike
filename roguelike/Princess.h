#pragma once

#include "GameObject.h"

class Princess : public GameObject {
public:
	Princess();
	explicit Princess(const Vec2d& origin);
};
