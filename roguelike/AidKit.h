#pragma once

#include "Character.h"
#include "Knight.h"

class AidKit : public GameObject {
public:
	AidKit(const Vec2d& origin);
	AidKit(const Vec2d& origin, uint32_t how_many);

	void collideWith(Knight& knight) override;

	void loadFromSettings(const std::string& classname) override;
private:
	uint32_t how_many;
};

