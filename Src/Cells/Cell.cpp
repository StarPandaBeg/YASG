#include "Cell.h"

#include "../GameConfig.h"

cells::Cell::Cell(sf::Vector2i position) : views::View(
	sf::Vector2f(
		(float)position.x * CFG_CELL_WIDTH,
		(float)position.y * CFG_CELL_HEIGHT
	), sf::Vector2f(
		CFG_CELL_WIDTH,
		CFG_CELL_HEIGHT
	)
), _gridPosition(position) {}

void cells::Cell::setGridPosition(sf::Vector2i position)
{
	_gridPosition = position;
	setPosition(sf::Vector2f(
		(float)position.x * CFG_CELL_WIDTH,
		(float)position.y * CFG_CELL_HEIGHT
	));
}
