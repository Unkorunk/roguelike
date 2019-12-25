#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>
#include <fstream>
#include <set>
#include <memory>

#include "Vec2d.h"
#include "GameObject.h"

class Map {
public:
	enum class GeneratorStates {
		UNDEFINED_OBJECT,
		GOOD_JOB,
		END
	};

	Map();
	Map(const std::string& filename);
	Map(size_t width, size_t height);

	char getSym(const Vec2d& origin) const;
	char getSym(size_t x, size_t y) const;

	size_t getWidth() const;
	size_t getHeight() const;

	void setData(const Map& other_map);

	void reg(char sym, const std::function<std::shared_ptr<GameObject>(size_t x, size_t y)>& creator);
	GeneratorStates gen(std::shared_ptr<GameObject>& output_go);
private:
	std::vector<std::string> data;
	std::map<char, std::function<std::shared_ptr<GameObject>(size_t x, size_t y)>> defined_types;
	size_t width, height;
};
