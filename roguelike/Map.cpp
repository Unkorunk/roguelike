#include "Map.h"

Map::Map() : width(2), height(2) {
	data.resize(height);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			data[i] += ' ';
		}
	}
	data[0][0] = 'K';
	data[1][1] = 'P';
}

Map::Map(const std::string& filename) {
	std::ifstream ifs(filename);
	ifs >> width >> height;
	ifs.ignore();
	data.resize(height);
	for (size_t i = 0; i < height; i++) {
		std::getline(ifs, data[i]);
	}
	ifs.close();
}

Map::Map(size_t width, size_t height) : width(width), height(height) {
	if (width < 6) {
		width = 6;
	}
	if (height < 6) {
		height = 6;
	}

	data.resize(height);
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			data[i] += '#';
		}
	}
	
	std::unique_ptr<Leaf> tree = split({1, 1, width - 2, height - 2}, 3);
	std::vector<Rect> rects;
	tree->getRects(rects);
	std::vector<Rect> rooms;
	for (auto &rect : rects) {
		Rect tmp(rect.x + 1 + (rect.width / 3 > 1 ? rand() % (rect.width / 3 - 1) : 1), rect.y + 1 + (rect.height / 3 > 1 ? rand() % (rect.height / 3 - 1) : 1), 0, 0);
		tmp.width = rect.width - (tmp.x - rect.x);
		tmp.height = rect.height - (tmp.y - rect.y);
		tmp.width -= (tmp.width / 3 != 0 ? rand() % (tmp.width / 3) : 0);
		tmp.height -= (tmp.height / 3 != 0 ? rand() % (tmp.height / 3) : 0);
		rooms.push_back(tmp);
	}

	for (auto rect : rooms) {
		for (size_t y = rect.y; y < rect.y + rect.height; y++) {
			for (size_t x = rect.x; x < rect.x + rect.width; x++) {
				data[y][x] = ' ';
			}
		}
	}

	Leaf::printPaths(tree, data);

	size_t knight_room = rand() % rooms.size();
	size_t princess_room = rand() % rooms.size();
	while (princess_room == knight_room) {
		princess_room = rand() % rooms.size();
	}

	data[rooms[knight_room].y + rooms[knight_room].height / 2][rooms[knight_room].x + rooms[knight_room].width / 2] = 'K';
	data[rooms[princess_room].y + rooms[princess_room].height / 2][rooms[princess_room].x + rooms[princess_room].width / 2] = 'P';

	size_t cnt_mobs = 1 + rand() % 20;
	for (size_t i = 0; i < cnt_mobs; i++) {
		size_t mob_room = rand() % rooms.size();
		size_t x = rooms[mob_room].x + rand() % rooms[mob_room].width;
		size_t y = rooms[mob_room].y + rand() % rooms[mob_room].height;

		while (data[y][x] != ' ') {
			mob_room = rand() % rooms.size();
			x = rooms[mob_room].x + rand() % rooms[mob_room].width;
			y = rooms[mob_room].y + rand() % rooms[mob_room].height;
		}

		switch (rand() % 3) {
		case 0:
			data[y][x] = 'Z';
			break;
		case 1:
			data[y][x] = 'D';
			break;
		default:
			data[y][x] = '+';
			break;
		}
	}
}

char Map::getSym(const Vec2d& origin) const {
	if (origin.x < width && origin.y < height) {
		return data[origin.y][origin.x];
	}
	throw std::out_of_range("Out of range");
}

char Map::getSym(size_t x, size_t y) const {
	if (x < width && y < height) {
		return data[y][x];
	}
	throw std::out_of_range("Out of range");
}

size_t Map::getWidth() const {
	return width;
}

size_t Map::getHeight() const {
	return height;
}

void Map::setData(const Map& other_map) {
	this->data = other_map.data;
	this->width = other_map.width;
	this->height = other_map.height;
}

void Map::reg(char sym, const std::function<std::shared_ptr<GameObject>(size_t x, size_t y)>& creator) {
	defined_types.try_emplace(sym, creator);
}

Map::GeneratorStates Map::gen(std::shared_ptr<GameObject>& output_go) {
	static size_t y = 0;
	static size_t x = 0;

	if (y < height && x < width) {
		if (defined_types.count(data[y][x]) == 0) {
			x++;
			if (x == width) {
				x = 0;
				y++;
			}
			return GeneratorStates::UNDEFINED_OBJECT;
		}

		output_go = defined_types[data[y][x]](x, y);
		x++;
		if (x == width) {
			x = 0;
			y++;
		}

		return GeneratorStates::GOOD_JOB;
	}

	return GeneratorStates::END;
}
