#include "CrateGenerationStep.h"

#include "../../Cells/CrateCell.h"

bool hasBorderCells(sf::Vector2i pos, grid::Grid* grid) {
	if (!grid->contains(pos + sf::Vector2i(1, 0))) return true;
	if (!grid->contains(pos + sf::Vector2i(-1, 0))) return true;
	if (!grid->contains(pos + sf::Vector2i(0, 1))) return true;
	if (!grid->contains(pos + sf::Vector2i(0, -1))) return true;
	return false;
}

bool generators::world::CrateGenerationStep::step(grid::Grid* grid)
{
	sf::Vector2i pos;
	int i = 0;
	sf::Vector2i size = grid->getSize();

	do {
		pos = getRandomPosition(size);
		i++;
	} while (!grid->contains(pos) || grid->get(pos) != nullptr || i >= 5 * size.x * size.y || hasBorderCells(pos, grid));
	if (i >= 10 * size.x * size.y) return false;

	grid->set(pos, new cells::CrateCell(pos, _destructable));
	return true;
}

void generators::world::CrateGenerationStep::process(grid::Grid* grid)
{
	for (int i = 0; i < _crateAmount; i++) {
		if (!step(grid)) break;
	}
}
