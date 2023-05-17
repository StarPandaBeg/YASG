#include "SnakeDecreaseCommand.h"

bool commands::SnakeDecreaseCommand::execute(snake::Snake* snake)
{
	snake->decrease(1);
	return true;
}
