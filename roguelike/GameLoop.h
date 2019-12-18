#pragma once

#include <vector>
#include <memory>
#include <string>

#include <curses.h>

#include "Map.h"
#include "GameObject.h"
#include "Dragon.h"
#include "Zombie.h"
#include "Knight.h"
#include "Princess.h"
#include "Wall.h"

class GameLoop {
public:
	GameLoop(const std::string& filename_map);

	void init();
	bool tick();
private:
	std::vector<std::shared_ptr<GameObject>> game_objs;
};
