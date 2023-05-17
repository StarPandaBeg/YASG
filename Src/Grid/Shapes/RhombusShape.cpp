#include "RhombusShape.h"

bool grid::shapes::RhombusShape::contains(sf::Vector2i point)
{
	return abs(point.x - _size.x / 2) + abs(point.y - _size.y / 2) < _size.x / 2;
}
