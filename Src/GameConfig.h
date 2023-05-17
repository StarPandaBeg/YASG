#pragma once

#include "SFML/Graphics.hpp"
#include "Grid/Shapes/IGridShape.h"

#include <string>

#define CFG_CELL_WIDTH 32
#define CFG_CELL_HEIGHT 32

#define CFG_WINDOW_WIDTH 1536
#define CFG_WINDOW_HEIGHT 768
#define CFG_WINDOW_TITLE "Yet Another Snake Game"

#define CFG_SNAKE_MAX_SPEED 2.0
#define CFG_SNAKE_SPEED_BASE 1.0
#define CFG_SNAKE_SPEED_COEF 0.2
#define CFG_SNAKE_CHANGE_EVERY 10
#define CFG_SNAKE_START_LENGTH 3

#define CFG_SCORE_MULTIPLY 20
#define CFG_HIGHSCORE_FILENAME "highscore.txt"

class GameConfigBuilder;
class GameConfig
{
private:
	std::string _playerName = "Player";

	sf::Vector2i _deskCellAmount = sf::Vector2i(64, 64);
	grid::shapes::IGridShape* _shape = nullptr;

	int _maxFoodAmount = 3;
	bool _allowDifferentFruits = true;
	bool _allowWoodCrates = true;
	bool _allowIronCrates = true;
	bool _allowPortals = true;
	bool _dieOnSelfTouch = false;
	bool _dieOnBorderTouch = true;

	int _woodCrateAmount = 50;
	int _ironCrateAmount = 50;

	int _seed = rand();
public:
	friend class GameConfigBuilder;

	sf::Vector2i getDeskSize();
	sf::Vector2i getDeskCellAmount();
	grid::shapes::IGridShape* getShape();

	int getMaxFoodAmount();
	bool allowDifferentFruits();
	bool allowWoodCrates();
	int getWoodCrateAmount();
	bool allowIronCrates();
	int getIronCrateAmount();
	bool allowPortals();
	bool dieOnSelfTouch();
	bool dieOnBorderTouch();
	std::string getPlayerName();

	int getSeed();

	static GameConfigBuilder getBuilder();
};

class GameConfigBuilder {
private:
	GameConfig _cfg;
public:
	GameConfigBuilder(GameConfig initial = GameConfig());

	GameConfigBuilder* setDeskSize(sf::Vector2i size);
	GameConfigBuilder* setShape(grid::shapes::IGridShape* shape);
	GameConfigBuilder* setMaxFoodAmount(int amount);
	GameConfigBuilder* setWoodCratesAmount(int amount);
	GameConfigBuilder* setIronCratesAmount(int amount);
	GameConfigBuilder* allowDifferentFruits(bool state);
	GameConfigBuilder* allowWoodCrates(bool state);
	GameConfigBuilder* allowIronCrates(bool state);
	GameConfigBuilder* allowPortals(bool state);
	GameConfigBuilder* allowTailCut(bool state);
	GameConfigBuilder* allowInfinityDesk(bool state);
	GameConfigBuilder* setPlayerName(std::string name);
	GameConfigBuilder* setSeed(int seed);

	GameConfig build();
};
