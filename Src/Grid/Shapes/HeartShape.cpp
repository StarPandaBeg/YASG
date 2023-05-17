#include "HeartShape.h"

bool grid::shapes::HeartShape::contains(sf::Vector2i point)
{
	point.x -= _size.x / 2;
	point.y -= _size.y / 2;
	auto x1 = -point.x / (0.75 * _size.x / 2);
	auto y1 = -point.y / (0.75 * _size.y / 2);

	return pow(x1 * x1 + y1 * y1 - 1, 3) - pow(x1 * 1.4, 2) * pow(y1, 3) < 0;
}
