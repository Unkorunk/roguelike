#include "GameLoop.h"

GameLoop::GameLoop(const std::string& filename_map) : map(filename_map) {
	auto simple_vaidator = [&](char sym, const Vec2d& origin) {
		for (auto go : game_objs) {
			auto character = std::dynamic_pointer_cast<Character>(go);
			if (character && character->isDied()) {
				continue;
			}
			
			if (go->getOrigin().x == origin.x && go->getOrigin().y == origin.y) {
				return go;
			}
		}

		return std::shared_ptr<GameObject>();
	};

	map.reg('#', [](size_t x, size_t y) { return std::make_shared<Wall>(Vec2d(x, y)); });
	map.reg('P', [](size_t x, size_t y) { return std::make_shared<Princess>(Vec2d(x, y)); });

	map.reg('K', [&simple_vaidator](size_t x, size_t y) { 
		auto knight = std::make_shared<Knight>(Vec2d(x, y));
		knight->setValidator(simple_vaidator);
		return knight;
	});
	map.reg('D', [&simple_vaidator](size_t x, size_t y) {
		auto dragon = std::make_shared<Dragon>(Vec2d(x, y));
		dragon->setValidator(simple_vaidator);
		return dragon;
	});
	map.reg('Z', [&simple_vaidator](size_t x, size_t y) {
		auto zombie = std::make_shared<Zombie>(Vec2d(x, y));
		zombie->setValidator(simple_vaidator);
		return zombie;
	});

	Map::GeneratorStates state;
	std::shared_ptr<GameObject> go;
	while ((state = map.gen(go)) != Map::GeneratorStates::END) {
		if (state == Map::GeneratorStates::GOOD_JOB) {
			game_objs.push_back(go);
		}
	}
}

void GameLoop::init() {
	for (auto go : game_objs) {
		move(go->getOrigin().y, go->getOrigin().x);
		addch(go->getSym());
	}
}

bool GameLoop::tick() {
	std::shared_ptr<Princess> princess;
	std::shared_ptr<Knight> knight;
	for (auto go : game_objs) {
		if (std::dynamic_pointer_cast<Princess>(go)) {
			princess = std::dynamic_pointer_cast<Princess>(go);
		} else if (std::dynamic_pointer_cast<Knight>(go)) {
			knight = std::dynamic_pointer_cast<Knight>(go);
		}
	}

	if (knight->isDied()) {
		return false;
	}

	for (auto go : game_objs) {
		auto character = std::dynamic_pointer_cast<Character>(go);
		if (character && !character->isDied()) {
			Vec2d old_origin = character->getOrigin();
			if (character->move()) {
				move(old_origin.y, old_origin.x);
				addch(' ');
				move(character->getOrigin().y, character->getOrigin().x);
				addch(character->getSym());
			}
		}
	}

	move(1, map.getWidth() + 1);
	printw("Health: %.2f", knight->getHP() * 100.0f / knight->getMaxHP());
	
	size_t id = 0;
	for (auto go : game_objs) {
		auto character = std::dynamic_pointer_cast<Character>(go);
		if (character && !std::dynamic_pointer_cast<Knight>(go)) {
			move(3 + id++, map.getWidth() + 1);
			printw("Character #%d: Health: %.2f", id, character->getHP() * 100.0f / character->getMaxHP());
		}
	}

	for (auto go : game_objs) {
		auto character = std::dynamic_pointer_cast<Character>(go);
		if (character) {
			if (character->isDied()) {
				character->remove();
			}
		}
	}

	if (princess->isWin()) {
		return false;
	}

	return true;
}
