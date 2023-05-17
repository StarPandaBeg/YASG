#include "Grid.h"

#include "SFML/Graphics.hpp"

#include <mutex>

using namespace grid;

void Grid::clear()
{
	std::lock_guard<std::mutex> gridLock{ lock };
	for (auto it = _cells.begin(); it != _cells.end(); it++) {
		delete it->second;
	}
	_cells.clear();
}

Grid::Grid(sf::Vector2i size)
{
	_size = size;
	clear();
}

grid::Grid::~Grid()
{
	for (auto it = _cells.begin(); it != _cells.end(); it++) {
		delete it->second;
	}
	delete _shape;
}

void grid::Grid::set(sf::Vector2i pos, cells::Cell* cell)
{
	std::lock_guard<std::mutex> gridLock{ lock };
	_cells[pos] = cell;
}

cells::Cell* grid::Grid::remove(sf::Vector2i pos)
{
	std::lock_guard<std::mutex> gridLock{ lock };
	if (_cells.find(pos) == _cells.end()) {
		return nullptr;
	}

	auto cell = _cells[pos];
	_cells.erase(pos);
	return cell;
}

cells::Cell* grid::Grid::get(sf::Vector2i pos)
{
	std::lock_guard<std::mutex> gridLock{ lock };
	if (_cells.find(pos) == _cells.end()) {
		return nullptr;
	}
	return _cells[pos];
}

CellMap* grid::Grid::getCells()
{
	return &_cells;
}

sf::Vector2i grid::Grid::getSize()
{
	return _size;
}

sf::Vector2i grid::Grid::getOppositePosition(sf::Vector2i pos, sf::Vector2i dir)
{
	auto startPos = pos;
	if (dir.x != 0)
		pos.x = dir.x == 1 ? 0 : getSize().x - 1;
	if (dir.y != 0)
		pos.y = dir.y == 1 ? 0 : getSize().y - 1;
	while (!contains(pos) && pos != startPos) pos += dir;
	pos -= dir;
	return pos;
}

shapes::IGridShape* grid::Grid::getShape()
{
	return _shape;
}

void grid::Grid::setShape(shapes::IGridShape* shape)
{
	if (_shape != nullptr) delete _shape;
	_shape = shape;
}

bool grid::Grid::contains(sf::Vector2i pos)
{
	if (_shape == nullptr) {
		if (pos.x < 0 || pos.x >= _size.x) return false;
		if (pos.y < 0 || pos.y >= _size.y) return false;
		return true;
	}
	return _shape->contains(pos);
}
