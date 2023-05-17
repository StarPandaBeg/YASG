#include "SnakeCell.h"

#include "../Commands/SnakeTailCutCommand.h"
#include "../Commands/SnakeDieCommand.h"
#include "../Util/ResourceManager.h"
#include "../SnakeGame.h"

commands::IHitCommand* cells::SnakeCell::onCollisionWith(cells::Cell* cell)
{
	if (SnakeGame::Current->getConfig().dieOnSelfTouch())
		return new commands::SnakeDieCommand();
	return new commands::SnakeTailCutCommand(this);
}

const char* cells::SnakeCell::getTextureId()
{
	return TEXTURE_SNAKE_BLOCK;
}

int cells::SnakeCell::getOrderInLayer()
{
	return LAYER_SNAKE;
}
