#include "PortalGenerationStep.h"

#include "../../Cells/TeleportCell.h"
#include <queue>

bool generators::world::PortalGenerationStep::step(grid::Grid* grid)
{
	auto posA = getFreePosition(grid);
	auto posB = getFreePosition(grid);
	if (posA.x == -1 || posB.x == -1) return false;

	auto portalA = new cells::TeleportCell(posA, posB);
	auto portalB = new cells::TeleportCell(posB, posA);

	portalA->setColor(_colors[_index]);
	portalB->setColor(_colors[_index]);

	grid->set(posA, portalA);
	grid->set(posB, portalB);

	return true;
}

sf::Vector2i generators::world::PortalGenerationStep::getFreePosition(grid::Grid* grid)
{
	sf::Vector2i pos;
	sf::Vector2i size = grid->getSize();
	int i = 0;
	do {
		pos = getRandomPosition(size);
		i++;
	} while (!grid->contains(pos) || grid->get(pos) != nullptr || i >= 5 * size.x * size.y);
	if (i >= 10 * size.x * size.y) return sf::Vector2i(-1, -1);

	return pos;
}

void generators::world::PortalGenerationStep::process(grid::Grid* grid)
{
	_index = 0;
	for (int i = 0; i < 3; i++) {
		if (!step(grid)) break;
		_index++;
	}
}
