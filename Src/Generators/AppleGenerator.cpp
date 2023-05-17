#include "AppleGenerator.h"
#include <exception>
#include <mutex>

cells::food::AppleCell* generators::AppleGenerator::getNewCell(sf::Vector2i position)
{
	cells::food::AppleCell* cell;
	if (_pool.size() > 0) {
		cell = _pool.front();
		_pool.pop();
		cell->setGridPosition(position);
	}
	else {
		cell = new cells::food::AppleCell(position);
	}
	_storage.push_back(cell);
	return cell;
}

sf::Vector2i generators::AppleGenerator::generate(int foodAmount)
{
	if (foodAmount < 0) throw std::range_error("Food amount should be greater or equal zero.");
	sf::Vector2i pos;
	int i = 0;

	do {
		pos.x = rand() % _grid->getSize().x;
		pos.y = rand() % _grid->getSize().y;
		i++;
	} while (_grid->get(pos) != nullptr || !_grid->contains(pos));
	if (i >= 100) throw std::runtime_error("New position for cell not found");

	auto cell = getNewCell(pos);
	cell->setFoodAmount(foodAmount);
	_grid->set(pos, cell);
	
	return pos;
}

bool generators::AppleGenerator::removeAt(sf::Vector2i gridPosition)
{
	auto cell = _grid->get(gridPosition);
	auto apple = static_cast<cells::food::AppleCell*>(cell);

	if (cell == nullptr) return false;
	auto found = std::find(_storage.begin(), _storage.end(), cell);
	if (found == _storage.end()) return false;

	_grid->remove(gridPosition);
	_storage.erase(found);
	_pool.push(apple);
	return true;
}
