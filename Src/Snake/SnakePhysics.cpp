#include "SnakePhysics.h"
#include "../Util/Utility.h"

#include "../SnakeGame.h"

void snake::SnakePhysics::movementTick()
{
	auto cellPositions = _snake->getCellPositions();
	auto headPos = _snake->getHead();
	auto headTargetPos = headPos + _currentDirection;
	auto head = _grid->get(headPos);
	static auto v = 0.0;

	for (auto it = cellPositions->begin(); it != cellPositions->end(); it++) {
		auto cell = _grid->get(*it);
		auto prevCell = it == cellPositions->begin() ? nullptr : _grid->get(*(it - 1));

		auto startPos = cell->getGridPosition();
		auto targetPos = cell == head ? headTargetPos : *(it - 1);
		auto startGlobalPos = util::Utility::toGlobalPosition(startPos);
		auto targetGlobalPos = util::Utility::toGlobalPosition(targetPos);

		auto diff = targetPos - startPos;
		if (abs(diff.x) > 1 || abs(diff.y) > 1) {
			cell->setGridPosition(targetPos);
			cell->setPosition(targetGlobalPos - (sf::Vector2f)_currentDirection);
			continue;
		}

		auto pos = util::Utility::vectorLerp(startGlobalPos, targetGlobalPos, v);
		cell->setPosition(pos);
	}

	auto diff = util::Utility::toGlobalPosition(headTargetPos) - head->getPosition();
	if (abs(diff.x) < 2 && abs(diff.y) < 2) {
		_snake->move(_currentDirection);
		_currentDirection = _nextDirection;
		_canMove = canMoveTo(_snake->getHead() + _currentDirection);
		v = 0;
	}
	else {
		v += 0.1 * _snake->getSpeed();
		v = v > 1 ? 1 : v;
	}
}

bool snake::SnakePhysics::canMoveTo(sf::Vector2i pos)
{
	if (_snake->getHead() == pos) return false;
	if (!_grid->contains(pos)) return onCollisionWithBorder(pos);
	auto collidedCell = _grid->get(pos);
	return collidedCell != nullptr ? onCollisionWith(collidedCell) : true;
}

void snake::SnakePhysics::tick()
{
	if (_snake->isDead()) return;
	if (_canMove) return movementTick();

	_currentDirection = _nextDirection;
	_canMove = canMoveTo(_snake->getHead() + _currentDirection);
}

void snake::SnakePhysics::setNextDirection(sf::Vector2i dir)
{
	_nextDirection = dir;
}

bool snake::SnakePhysics::onCollisionWith(cells::Cell* cell)
{
	auto head = _grid->get(_snake->getHead());
	auto command = cell->onCollisionWith(head);
	if (command == nullptr) return true;

	auto result = command->execute(_snake);
	delete command;
	return result;
}

bool snake::SnakePhysics::onCollisionWithBorder(sf::Vector2i pos)
{
	if (SnakeGame::Current->getConfig().dieOnBorderTouch()) {
		_snake->die();
		return false;
	}
	auto moveDirection = pos - _snake->getHead();
	auto newPos = _grid->getOppositePosition(pos, moveDirection);
	_snake->teleport(newPos);
	_currentDirection = _nextDirection;
	return false;
}

void snake::SnakePhysics::onSnakeBeforeTeleport(const events::Event& e)
{
	auto ev = static_cast<const events::snake::SnakeBeforeTeleportEvent&>(e);
	
	if (!_grid->contains(ev.position)) return;
	auto targetCell = _grid->get(ev.position);
	if (targetCell != nullptr) {
		onCollisionWith(targetCell);
	}
}

void snake::SnakePhysics::onSnakeTeleport(const events::Event& e)
{
	auto ev = static_cast<const events::snake::SnakeTeleportedEvent&>(e);
	if (!_grid->contains(ev.from)) return;
	if (!_grid->contains(ev.position)) {
		onCollisionWithBorder(ev.position + _currentDirection);
		return;
	}
	_canMove = canMoveTo(_snake->getHead() + _currentDirection);
}

snake::SnakePhysics::SnakePhysics(snake::Snake* snake, grid::Grid* grid) : _snake(snake), _grid(grid)
{
	_eventIds[0] = _snake->on<events::snake::SnakeBeforeTeleportEvent>(std::bind(&snake::SnakePhysics::onSnakeBeforeTeleport, this, std::placeholders::_1));
	_eventIds[1] = _snake->on<events::snake::SnakeTeleportedEvent>(std::bind(&snake::SnakePhysics::onSnakeTeleport, this, std::placeholders::_1));
}

snake::SnakePhysics::~SnakePhysics()
{
	_snake->off<events::snake::SnakeBeforeTeleportEvent>(_eventIds[0]);
	_snake->off<events::snake::SnakeTeleportedEvent>(_eventIds[1]);
}

sf::Vector2i snake::SnakePhysics::getCurrentDirrection()
{
	return _currentDirection;
}

void snake::SnakePhysics::reset()
{
	_currentDirection = sf::Vector2i(0, 0);
	_nextDirection = sf::Vector2i(0, 0);
}
