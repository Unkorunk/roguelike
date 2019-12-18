#include "GameLoop.h"

GameLoop::GameLoop(const std::string& filename_map) {
	Map map(filename_map);

	auto simple_vaidator = [&](char sym, const Vec2d& origin) {
		for (auto go : game_objs) {
			if (go->getOrigin().x == origin.x && go->getOrigin().y == origin.y) {
				return false;
			}
		}
		return (origin.x > 0 && origin.y > 0);
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
	for (auto go : game_objs) {
		auto character = std::dynamic_pointer_cast<Character>(go);
		if (character) {
			Vec2d old_origin = character->getOrigin();
			if (character->move()) {
				move(old_origin.y, old_origin.x);
				addch(' ');
				move(character->getOrigin().y, character->getOrigin().x);
				addch(character->getSym());
			}
		}
	}

	std::shared_ptr<Knight> knight;
	std::shared_ptr<Princess> princess;
	for (auto go : game_objs) {
		if (std::dynamic_pointer_cast<Knight>(go)) {
			knight = std::dynamic_pointer_cast<Knight>(go);
		} else if (std::dynamic_pointer_cast<Princess>(go)) {
			princess = std::dynamic_pointer_cast<Princess>(go);
		}
	}

	if (Vec2d::distance(knight->getOrigin(), princess->getOrigin()) == 1) {
		return false;
	}

	return true;
}
