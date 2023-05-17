#pragma once

#include <vector>
#include <queue>
#include "../Cells/Food/AppleCell.h"
#include "../Grid/Grid.h"

namespace generators {
	class AppleGenerator {
	private:
		std::queue<cells::food::AppleCell*> _pool;
		std::vector<cells::food::AppleCell*> _storage;
		grid::Grid* _grid;

		cells::food::AppleCell* getNewCell(sf::Vector2i position);
	public:
		AppleGenerator(grid::Grid* grid) : _grid(grid) {}
		sf::Vector2i generate(int foodAmount = 1);
		bool removeAt(sf::Vector2i gridPosition);
	};
}