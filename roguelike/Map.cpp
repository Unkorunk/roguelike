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
			data[i] += ' ';
		}
	}

	struct Room {
		size_t x, y, width, height;
	};
	
	// TODO: generation
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
