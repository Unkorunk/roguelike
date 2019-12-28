#pragma once

#include <random>

class Utility {
public:
	static int random() {
		static std::default_random_engine engine;
		static std::uniform_int_distribution distribution;
		return distribution(engine);
	}
};