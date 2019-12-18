#include "Map.h"

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

char Map::getSym(const Vec2d& origin) {
	if (origin.x < width && origin.y < height) {
		return data[origin.y][origin.x];
	}
	throw std::out_of_range("Out of range");
}

char Map::getSym(size_t x, size_t y) {
	if (x < width && y < height) {
		return data[y][x];
	}
	throw std::out_of_range("Out of range");
}

size_t Map::getWidth() {
	return width;
}

size_t Map::getHeight() {
	return height;
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
