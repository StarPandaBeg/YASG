#include "CrateCell.h"

#include "../Commands/SnakeDecreaseCommand.h"
#include "../Commands/SnakeDieCommand.h"
#include "../Util/ResourceManager.h"

cells::CrateCell::CrateCell(sf::Vector2i position, bool destructable) : Cell(position), _destructable(destructable) {}

commands::IHitCommand* cells::CrateCell::onCollisionWith(Cell* cell)
{
	if (_destructable) return new commands::SnakeDecreaseCommand();
	return new commands::SnakeDieCommand();
}

const char* cells::CrateCell::getTextureId() {
	return _destructable ? TEXTURE_CRATE_WOOD : TEXTURE_CRATE_METAL;
}