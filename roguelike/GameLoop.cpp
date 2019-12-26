#include "GameLoop.h"

GameLoop::GameLoop() {
	simple_vaidator = [&](char sym, const Vec2d& origin) {
		for (auto go : game_objs) {
			if (go->getRemoved()) {
				continue;
			}

			auto character = std::dynamic_pointer_cast<Character>(go);
			if (character && character->isDied()) {
				continue;
			}
			
			if (go->getOrigin() == origin) {
				return go;
			}
		}

		return std::shared_ptr<GameObject>();
	};

	map.reg('#', [](size_t x, size_t y) { return std::make_shared<Wall>(Vec2d(x, y)); });
	map.reg('P', [](size_t x, size_t y) { return std::make_shared<Princess>(Vec2d(x, y)); });
	map.reg('+', [](size_t x, size_t y) { return std::make_shared<AidKit>(Vec2d(x, y)); });

	map.reg('K', [&](size_t x, size_t y) { 
		auto knight = std::make_shared<Knight>(Vec2d(x, y));
		knight->setValidator(simple_vaidator);
		return knight;
	});
	map.reg('D', [&](size_t x, size_t y) {
		auto dragon = std::make_shared<Dragon>(Vec2d(x, y));
		dragon->setValidator(simple_vaidator);
		return dragon;
	});
	map.reg('Z', [&](size_t x, size_t y) {
		auto zombie = std::make_shared<Zombie>(Vec2d(x, y));
		zombie->setValidator(simple_vaidator);
		return zombie;
	});
}

GameLoop::GameLoop(const std::string& filename) : GameLoop() {
	this->map.setData(Map(filename));
}

GameLoop::GameLoop(size_t width, size_t height) : GameLoop() {
	this->map.setData(Map(width, height));
}

void GameLoop::init() {
	Map::GeneratorStates state;
	std::shared_ptr<GameObject> go;
	while ((state = map.gen(go)) != Map::GeneratorStates::END) {
		if (state == Map::GeneratorStates::GOOD_JOB) {
			game_objs.push_back(go);
		}
	}

	for (auto go : game_objs) {
		move(go->getOrigin().y, go->getOrigin().x);
		addch(go->getSym());
	}
}

GameLoop::TickState GameLoop::tick() {
	// Remove object is died
	for (auto iter = game_objs.begin(); iter != game_objs.end(); ) {
		auto character = std::dynamic_pointer_cast<Character>(*iter);
		if (character && character->isDied()) {
			iter = game_objs.erase(iter);
		} else {
			iter++;
		}
	}
	// ~Remove object is died

	if (is_termresized()) {
		resize_term(0, 0);
	}

	//clear();
	//for (auto go : game_objs) {
	//	if (!go->getRemoved()) {
	//		move(go->getOrigin().y, go->getOrigin().x);
	//		addch(go->getSym());
	//	}
	//}

	// Get knight and princess
	std::shared_ptr<Princess> princess;
	std::shared_ptr<Knight> knight;
	for (auto go : game_objs) {
		if (std::dynamic_pointer_cast<Princess>(go)) {
			princess = std::dynamic_pointer_cast<Princess>(go);
		} else if (std::dynamic_pointer_cast<Knight>(go)) {
			knight = std::dynamic_pointer_cast<Knight>(go);
		}
	}

	if (!knight || !princess || knight->isDied()) {
		return TickState::eLose;
	}
	// ~Get knight and princess

	// move bullets
	for (auto go : game_objs) {
		auto bullet = std::dynamic_pointer_cast<Bullet>(go);
		if (bullet && !bullet->isDied()) {
			Vec2d old_origin = bullet->getOrigin();
			if (bullet->move()) {
		/*		move(old_origin.y, old_origin.x);
				addch(' ');
				move(bullet->getOrigin().y, bullet->getOrigin().x);
				addch(bullet->getSym());*/
			}
		}
	}
	// ~move bullets

	// make died bullets invisible
	for (auto go : game_objs) {
		auto bullet = std::dynamic_pointer_cast<Bullet>(go);
		if (bullet) {
			if (bullet->isDied()) {
				bullet->remove();
			}
		}
	}
	// ~make died bullets invisible

	// move and shoot other objects
	std::vector<std::shared_ptr<Bullet>> new_bullets;

	for (auto go : game_objs) {
		auto character = std::dynamic_pointer_cast<Character>(go);
		if (character && !std::dynamic_pointer_cast<Bullet>(character) && !character->isDied()) {
			Vec2d old_origin = character->getOrigin();
			if (character->move()) {
				//move(old_origin.y, old_origin.x);
				//addch(' ');
				//move(character->getOrigin().y, character->getOrigin().x);
				//addch(character->getSym());

				character->setAim((int)character->getOrigin().x - (int)old_origin.x, (int)character->getOrigin().y - (int)old_origin.y);
			}

			std::pair<int, int> bullet_params;
			if (character->shoot(bullet_params)) {
				new_bullets.push_back(std::make_shared<Bullet>(character->getOrigin() + bullet_params, bullet_params));
				new_bullets.back()->setValidator(character->getValidator());
				new_bullets.back()->setDamage(character->getDamage());
			}
		}
	}
	// ~move and shoot other objects

	// logic for new bullets
	for (auto bullet : new_bullets) {
		auto collision_obj = bullet->getValidator()(bullet->getSym(), bullet->getOrigin());

		if (collision_obj) {
			auto character = std::dynamic_pointer_cast<Character>(collision_obj);
			if (character) {
				character->collideWith(*bullet.get());
			}
		} else {
			//move(bullet->getOrigin().y, bullet->getOrigin().x);
			//addch('*');
			game_objs.push_back(bullet);
		}
	}
	// ~logic for new bullets

	// make died objs invisible
	for (auto go : game_objs) {
		auto character = std::dynamic_pointer_cast<Character>(go);
		if (character) {
			if (character->isDied()) {
				character->remove();
			}
		}
	}
	// ~make died objs invisible
	
	// fog
	clear();
	const size_t fog_distance = 6;
	for (auto go : game_objs) {
		if (Vec2d::distance(go->getOrigin(), knight->getOrigin()) < fog_distance) {
			auto character = std::dynamic_pointer_cast<Character>(go);
			if (character && character->isDied()) {
				continue;
			}

			if (!go->getRemoved()) {
				move(go->getOrigin().y, go->getOrigin().x);
				addch(go->getSym());
			}
		}
	}

	Vec2d left_bound = knight->getOrigin() - Vec2d(fog_distance, fog_distance);
	Vec2d right_bound = knight->getOrigin() + Vec2d(fog_distance, fog_distance);
	right_bound.x = std::min(right_bound.x, map.getWidth() - 1);
	right_bound.y = std::min(right_bound.y, map.getHeight() - 1);
	for (size_t y = left_bound.y; y <= right_bound.y; y++) {
		for (size_t x = left_bound.x; x <= right_bound.x; x++) {
			if (Vec2d::distance(Vec2d(x, y), knight->getOrigin()) == fog_distance) {
				move(y, x);
				addch('@');
			}
		}
	}

	// ~fog

	// info
#if _DEBUG
	move(1, map.getWidth() + 1);
	printw("Health: %d / %d", knight->getHP(), knight->getMaxHP());

	move(2, map.getWidth() + 1);
	printw("GameObjs: %3d", game_objs.size());

	size_t id = 0;
	for (auto go : game_objs) {
		auto character = std::dynamic_pointer_cast<Character>(go);
		if (character && !character->isDied() && !std::dynamic_pointer_cast<Knight>(go) && !std::dynamic_pointer_cast<Bullet>(go)) {
			move(3 + id++, map.getWidth() + 1);
			printw("%s #%d: Health: %d / %d", typeid(*character).name(), id, character->getHP(), character->getMaxHP());
		}

		if (id >= 10) {
			break;
		}
	}
#endif
	// ~info

	if (princess->isWin()) {
		return TickState::eWin;
	}

	return TickState::eContinue;
}
