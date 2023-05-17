#include "GameConfig.h"

sf::Vector2i GameConfig::getDeskSize()
{
	return sf::Vector2i(
		_deskCellAmount.x * CFG_CELL_WIDTH,
		_deskCellAmount.y * CFG_CELL_HEIGHT
	);
}

sf::Vector2i GameConfig::getDeskCellAmount()
{
	return _deskCellAmount;
}

grid::shapes::IGridShape* GameConfig::getShape()
{
	return _shape;
}

int GameConfig::getMaxFoodAmount()
{
	return _maxFoodAmount;
}

bool GameConfig::allowDifferentFruits()
{
	return _allowDifferentFruits;
}

bool GameConfig::allowWoodCrates()
{
	return _allowWoodCrates;
}

int GameConfig::getWoodCrateAmount()
{
	return _woodCrateAmount;
}

bool GameConfig::allowIronCrates()
{
	return _allowIronCrates;
}

int GameConfig::getIronCrateAmount()
{
	return _ironCrateAmount;
}

bool GameConfig::allowPortals()
{
	return _allowPortals;
}

bool GameConfig::dieOnSelfTouch()
{
	return _dieOnSelfTouch;
}

bool GameConfig::dieOnBorderTouch()
{
	return _dieOnBorderTouch;
}

std::string GameConfig::getPlayerName()
{
	return _playerName;
}

int GameConfig::getSeed()
{
	return _seed;
}

GameConfigBuilder GameConfig::getBuilder()
{
	return GameConfigBuilder();
}

GameConfigBuilder::GameConfigBuilder(GameConfig initial)
{
	_cfg = initial;
	_cfg._seed = rand();
}

GameConfigBuilder* GameConfigBuilder::setMaxFoodAmount(int amount)
{
	_cfg._maxFoodAmount = amount;
	return this;
}

GameConfigBuilder* GameConfigBuilder::setDeskSize(sf::Vector2i size) {
	_cfg._deskCellAmount = size;
	return this;
}

GameConfigBuilder* GameConfigBuilder::setShape(grid::shapes::IGridShape* shape) {
	delete _cfg._shape;
	_cfg._shape = shape;
	return this;
}

GameConfigBuilder* GameConfigBuilder::setWoodCratesAmount(int amount)
{
	_cfg._woodCrateAmount = amount;
	return this;
}

GameConfigBuilder* GameConfigBuilder::setIronCratesAmount(int amount)
{
	_cfg._ironCrateAmount = amount;
	return this;
}

GameConfigBuilder* GameConfigBuilder::allowDifferentFruits(bool state)
{
	_cfg._allowDifferentFruits = state;
	return this;
}

GameConfigBuilder* GameConfigBuilder::allowWoodCrates(bool state)
{
	_cfg._allowWoodCrates = state;
	return this;
}

GameConfigBuilder* GameConfigBuilder::allowIronCrates(bool state)
{
	_cfg._allowIronCrates = state;
	return this;
}

GameConfigBuilder* GameConfigBuilder::allowPortals(bool state)
{
	_cfg._allowPortals = state;
	return this;
}

GameConfigBuilder* GameConfigBuilder::allowTailCut(bool state)
{
	_cfg._dieOnSelfTouch = !state;
	return this;
}

GameConfigBuilder* GameConfigBuilder::allowInfinityDesk(bool state)
{
	_cfg._dieOnBorderTouch = !state;
	return this;
}

GameConfigBuilder* GameConfigBuilder::setPlayerName(std::string name) {
	_cfg._playerName = name;
	return this;
}

GameConfig GameConfigBuilder::build() {
	return _cfg;
}

GameConfigBuilder* GameConfigBuilder::setSeed(int seed)
{
	_cfg._seed = seed;
	return this;
}
