#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>
#include <fstream>
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

	Map() = delete;
	Map(const std::string& filename);

	char getSym(const Vec2d& origin);
	char getSym(size_t x, size_t y);

	size_t getWidth();
	size_t getHeight();

	void reg(char sym, const std::function<std::shared_ptr<GameObject>(size_t x, size_t y)>& creator);
	GeneratorStates gen(std::shared_ptr<GameObject>& output_go);
private:
	std::vector<std::string> data;
	std::map<char, std::function<std::shared_ptr<GameObject>(size_t x, size_t y)>> defined_types;
	size_t width, height;
};
