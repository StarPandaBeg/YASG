#include "SnakeEatCommand.h"

bool commands::SnakeEatCommand::execute(snake::Snake* snake)
{
	snake->eat(_apple);
	return true;
}
