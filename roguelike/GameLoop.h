#pragma once

#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <curses.h>
#include <algorithm>

#include "Map.h"
#include "GameObject.h"
#include "Dragon.h"
#include "Zombie.h"
#include "Knight.h"
#include "Princess.h"
#include "Wall.h"
#include "AidKit.h"

class GameLoop {
public:
	enum class TickState {
		eContinue,
		eWin,
		eLose
	};

	GameLoop(const std::string& filename);
	GameLoop(size_t width, size_t height);

	void init();
	TickState tick();
private:
	GameLoop();

	std::function<std::shared_ptr<GameObject>(char sym, const Vec2d & origin)> simple_vaidator;
	std::vector<std::shared_ptr<GameObject>> game_objs;
	Map map;
};
