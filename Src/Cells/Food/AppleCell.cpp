#include "AppleCell.h"
#include <exception>

#include "../../Commands/SnakeEatCommand.h"

commands::IHitCommand* cells::food::AppleCell::onCollisionWith(cells::Cell* cell)
{
	return new commands::SnakeEatCommand(this);
}

const char* cells::food::AppleCell::getTextureId()
{
	if ((_foodAmount-1) >= _textures.size()) return *(_textures.end() - 1);
	return _textures[_foodAmount-1];
}

int cells::food::AppleCell::getFoodAmount()
{
	return _foodAmount;
}

void cells::food::AppleCell::setFoodAmount(int foodAmount)
{
	if (foodAmount < 0) throw std::range_error("Food amount should be greater or equal zero.");
	_foodAmount = foodAmount;
}
