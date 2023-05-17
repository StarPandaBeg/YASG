#pragma once

#include "GameConfig.h"
#include "Events/Event.h"
#include "Events/EventDispatcher.h"
#include "Generators/AppleGenerator.h"
#include "Grid/Grid.h"
#include "Snake/Snake.h"
#include "Snake/SnakePhysics.h"
#include "Snake/SnakeRenderer.h"
#include "Util/ITickable.h"
#include "Util/Clock.h"

namespace events {
	namespace game {
		struct GameStartedEvent : events::Event {};
		struct GamePausedEvent : events::Event {
			bool state;
			GamePausedEvent(bool state) : state(state) {}
		};
		struct GameOverEvent : events::Event {};

		struct ScoreUpdateEvent : events::Event {
			int value;
			ScoreUpdateEvent(int value) : value(value) {}
		};
		struct ClockUpdateEvent : events::Event {
			sf::Time time;
			ClockUpdateEvent(sf::Time time) : time(time) {}
		};
	}
}

class SnakeGame : public events::EventDispatcher, public util::ITickable
{
private:
	GameConfig _cfg;
	grid::Grid* _grid;
	snake::Snake* _snake;
	snake::SnakePhysics* _physics;
	snake::SnakeRenderer* _renderer;
	generators::AppleGenerator* _appleGenerator;

	int _score = 0;
	bool _paused = false;
	bool _run = false;
	util::Clock _clock;

	int _eventIds[5] = {};
	int _timerIds[1] = {};

	void onMovementInputEvent(const events::Event& e);
	void onKeyInputEvent(const events::Event& e);
	void onAppleEaten(const events::Event& e);
	void onLengthChanged(const events::Event& e);
	void onDie(const events::Event& e);
	int getNextFruit();
	void setScore(int score);
public:
	static SnakeGame* Current;

	SnakeGame(GameConfig cfg);
	~SnakeGame();

	void run();
	void stop();
	void reset();
	void setPaused(bool state);

	grid::Grid* getGrid();
	snake::Snake* getSnake();
	snake::SnakePhysics* getPhysics();
	GameConfig getConfig();
	int getScore();
	sf::Time getTime();

	void tick() override;
};
