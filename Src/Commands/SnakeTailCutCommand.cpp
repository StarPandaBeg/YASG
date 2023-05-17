#include "SnakeTailCutCommand.h"

bool commands::SnakeTailCutCommand::execute(snake::Snake* snake)
{
	auto cells = snake->getCellPositions();
	auto found = std::find(cells->begin(), cells->end(), _cell->getGridPosition());
	auto dist = std::distance(cells->begin(), found);

	auto buffSize = snake->getLength(true) - snake->getLength();
	snake->decrease(snake->getLength() - dist + buffSize);
	return true;
}