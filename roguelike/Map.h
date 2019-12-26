#pragma once

#include <vector>
#include <string>
#include <functional>
#include <map>
#include <fstream>
#include <set>
#include <memory>

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
	struct Rect {
		size_t x, y, width, height;
		Rect() : x(), y(), width(), height() {}
		Rect(size_t x, size_t y, size_t width, size_t height) : x(x), y(y), width(width), height(height) {}
		Rect(const Rect& rect) : x(rect.x), y(rect.y), width(rect.width), height(rect.height) {}
	};
	struct Leaf {
		Rect rect;
		std::unique_ptr<Leaf> left;
		std::unique_ptr<Leaf> right;

		Leaf(Rect rect) : rect(rect), left(), right() {}
		void getRects(std::vector<Rect>& rooms) {
			if (left) {
				left->getRects(rooms);
				right->getRects(rooms);
			} else {
				rooms.push_back(rect);
			}
		}

		static void printPaths(const std::unique_ptr<Leaf>& tree, std::vector<std::string>& map) {
			if (tree->left) {
				int deltaX = tree->right->rect.x + tree->right->rect.width / 2 - (tree->left->rect.x + tree->left->rect.width / 2);
				int deltaY = tree->right->rect.y + tree->right->rect.height / 2 - (tree->left->rect.y + tree->left->rect.height / 2);;

				if (deltaX < 0) {
					deltaX = -1;
				} else if (deltaX != 0) {
					deltaX = 1;
				}

				if (deltaY < 0) {
					deltaY = -1;
				} else if (deltaY != 0) {
					deltaY = 1;
				}

				int nowX = tree->left->rect.x + tree->left->rect.width / 2;
				int nowY = tree->left->rect.y + tree->left->rect.height / 2;
				while (nowX != tree->right->rect.x + tree->right->rect.width / 2 || nowY != tree->right->rect.y + tree->right->rect.height / 2) {
					map[nowY][nowX] = ' ';
					nowX += deltaX;
					nowY += deltaY;
				}
				map[nowY][nowX] = ' ';

				printPaths(tree->left, map);
				printPaths(tree->right, map);
			}
		}
	};

	std::unique_ptr<Leaf> split(Rect rect, size_t iter) {
		std::unique_ptr<Leaf> root = std::make_unique<Leaf>(rect);
		if (iter != 0) {
			Rect rect1;
			Rect rect2;

			do {
				if (rand() % 2 == 0) {
					rect1 = { rect.x, rect.y, 1 + rand() % rect.width, rect.height };
					rect2 = { rect.x + rect1.width, rect.y, rect.width - rect1.width, rect.height };
				} else {
					rect1 = { rect.x, rect.y, rect.width, 1 + rand() % rect.height };
					rect2 = { rect.x, rect.y + rect1.height, rect.width, rect.height - rect1.height };
				}
			} while (rect1.height < 3 || rect2.height < 3 || rect1.width < 3 || rect2.width < 3 ||
				rect1.width * 1.0f / rect1.height < 0.45f || rect2.width * 1.0f / rect2.height < 0.45f);

			root->left = split(rect1, iter - 1);
			root->right = split(rect2, iter - 1);
		}
		return root;
	}

	std::vector<std::string> data;
	std::map<char, std::function<std::shared_ptr<GameObject>(size_t x, size_t y)>> defined_types;
	size_t width, height;
};
