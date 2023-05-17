#include "EllipseShape.h"

bool grid::shapes::EllipseShape::contains(sf::Vector2i point)
{
	auto size = _size;
	point.x -= size.x / 2 - 1;
	point.y -= size.y / 2 - 1;
	size.x /= 2;
	size.y /= 2;

	return (((float)point.x * point.x) / (size.x * size.x) + ((float)point.y * point.y) / (size.y * size.y)) < 1;
}
