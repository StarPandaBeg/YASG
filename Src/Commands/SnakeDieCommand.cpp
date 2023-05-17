#include "SnakeDieCommand.h"

bool commands::SnakeDieCommand::execute(snake::Snake* snake)
{
	snake->die();
	return false;
}
