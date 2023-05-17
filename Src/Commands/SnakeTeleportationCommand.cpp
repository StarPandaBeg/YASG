#include "SnakeTeleportationCommand.h"

bool commands::SnakeTeleportationCommand::execute(snake::Snake* snake)
{
	snake->teleport(_to);
	return true;
}
