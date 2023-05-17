#include "SnakeGame.h"

#include "Generators/World/WorldGenerator.h"
#include "Util/InputSystem.h"
#include "Util/GameTimer.h"
#include "Util/Utility.h"
#include "Util/HighScoreManager.h"

#include <exception>

SnakeGame* SnakeGame::Current = nullptr;

void SnakeGame::onMovementInputEvent(const events::Event& e)
{
	if (_paused) return;
	auto ev = static_cast<const events::input::MovementEvent&>(e); sf::Vector2i movement;

	if (ev.direction == events::input::MovementDirection::UP) movement.y = -1;
	if (ev.direction == events::input::MovementDirection::DOWN) movement.y = 1;
	if (ev.direction == events::input::MovementDirection::LEFT) movement.x = -1;
	if (ev.direction == events::input::MovementDirection::RIGHT) movement.x = 1;

	auto diff = _physics->getCurrentDirrection() + movement;
	if (diff.x == 0 && diff.y == 0 && _snake->getLength(true) > 1) return;
	_physics->setNextDirection(movement);
}

void SnakeGame::onKeyInputEvent(const events::Event& e)
{
	auto ev = static_cast<const events::input::KeyEvent&>(e); sf::Vector2i movement;
	if (ev.e.code == sf::Keyboard::Escape) setPaused(!_paused);
}

void SnakeGame::onAppleEaten(const events::Event& e)
{
	auto ev = static_cast<const events::snake::AppleEatenEvent&>(e);
	_appleGenerator->removeAt(ev.position);

	try {
		_appleGenerator->generate(getNextFruit());
	}
	catch (...) {

	}
}

void SnakeGame::onLengthChanged(const events::Event& e)
{
	auto ev = static_cast<const events::snake::SnakeLengthChangedEvent&>(e);

	auto nextSpeed = CFG_SNAKE_SPEED_BASE + CFG_SNAKE_SPEED_COEF * (ev.to / CFG_SNAKE_CHANGE_EVERY);
	nextSpeed = util::Utility::constrain(nextSpeed, (double)_snake->getSpeed(), CFG_SNAKE_MAX_SPEED);
	_snake->setSpeed(nextSpeed);
	setScore(CFG_SCORE_MULTIPLY * (ev.to - CFG_SNAKE_START_LENGTH));
}

void SnakeGame::onDie(const events::Event& e)
{
	stop();
	util::HighScoreManager::instance()->add(util::ScoreRow(_cfg.getPlayerName(), _score, _clock.getElapsedTime().asSeconds()));
	emit(events::game::GameOverEvent());
}

int SnakeGame::getNextFruit()
{
	if (!_cfg.allowDifferentFruits()) return 1;
	auto val = rand() % 10;
	if (val < 2) return 3;
	if (val < 5) return 2;
	return 1;
}

void SnakeGame::setScore(int score)
{
	_score = score;
	emit(events::game::ScoreUpdateEvent(score));
}

void SnakeGame::setPaused(bool state)
{
	_paused = state;
	emit(events::game::GamePausedEvent(state));
	_clock.setState(!state);
}

SnakeGame::SnakeGame(GameConfig cfg)
{
	if (SnakeGame::Current != nullptr) throw std::runtime_error("SnakeGame instance already instantiated");
	SnakeGame::Current = this;

	_cfg = cfg;
	_grid = new grid::Grid(cfg.getDeskCellAmount());
	_grid->setShape(_cfg.getShape());

	auto mid = util::Utility::getMid(_grid->getSize());

	_snake = new snake::Snake(sf::Vector2i(0, 0));
	_physics = new snake::SnakePhysics(_snake, _grid);
	_renderer = new snake::SnakeRenderer(_snake, _grid);
	_appleGenerator = new generators::AppleGenerator(_grid);
	_snake->setSpeed(CFG_SNAKE_SPEED_BASE);

	_eventIds[0] = _snake->on<events::snake::AppleEatenEvent>(std::bind(&SnakeGame::onAppleEaten, this, std::placeholders::_1));
	_eventIds[1] = _snake->on<events::snake::SnakeDiedEvent>(std::bind(&SnakeGame::onDie, this, std::placeholders::_1));
	_eventIds[2] = _snake->on<events::snake::SnakeLengthChangedEvent>(std::bind(&SnakeGame::onLengthChanged, this, std::placeholders::_1));

	reset();
}

SnakeGame::~SnakeGame()
{
	if (_run) stop();
	_snake->off<events::snake::SnakeLengthChangedEvent>(_eventIds[2]);
	_snake->off<events::snake::SnakeDiedEvent>(_eventIds[1]);
	_snake->off<events::snake::AppleEatenEvent>(_eventIds[0]);

	delete _appleGenerator;
	delete _renderer;
	delete _physics;
	delete _snake;
	delete _grid;

	SnakeGame::Current = nullptr;
}

void SnakeGame::run()
{
	// reset();
	_eventIds[3] = util::InputSystem::instance()->on<events::input::MovementEvent>(std::bind(&SnakeGame::onMovementInputEvent, this, std::placeholders::_1));
	_eventIds[4] = util::InputSystem::instance()->on<events::input::KeyEvent>(std::bind(&SnakeGame::onKeyInputEvent, this, std::placeholders::_1));

	_clock.restart();
	setPaused(false);

	_snake->increase(CFG_SNAKE_START_LENGTH - 1);
	setScore(0);
	_timerIds[0] = util::GameTimer::Default->add(this);
	for (int i = 0; i < _cfg.getMaxFoodAmount(); i++) _appleGenerator->generate(getNextFruit());

	_run = true;
	emit(events::game::GameStartedEvent());
}

void SnakeGame::stop()
{
	_run = false;
	util::InputSystem::instance()->off<events::input::KeyEvent>(_eventIds[4]);
	util::InputSystem::instance()->off<events::input::MovementEvent>(_eventIds[3]);
	util::GameTimer::Default->remove(_timerIds[0]);
}

void SnakeGame::reset()
{
	auto size = _grid->getSize();
	auto mid = util::Utility::getMid(size);

	_grid->clear();
	auto worldGen = generators::world::WorldGenerator::fromConfig(_cfg);
	worldGen->run(_grid);
	delete worldGen;

	_snake->reset(mid);
	_renderer->reset();
	_physics->reset();
}

grid::Grid* SnakeGame::getGrid()
{
	return _grid;
}

snake::Snake* SnakeGame::getSnake()
{
	return _snake;
}

snake::SnakePhysics* SnakeGame::getPhysics()
{
	return _physics;
}

GameConfig SnakeGame::getConfig()
{
	return _cfg;
}

int SnakeGame::getScore()
{
	return _score;
}

sf::Time SnakeGame::getTime()
{
	return _clock.getElapsedTime();
}

void SnakeGame::tick()
{
	if (_paused) return;
	_physics->tick();
	emit(events::game::ClockUpdateEvent(_clock.getElapsedTime()));
}
