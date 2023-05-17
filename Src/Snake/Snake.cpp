#include "Snake.h"

#include "../Cells/Food/AppleCell.h"

void snake::Snake::_emitMove()
{
	auto cells = getCellPositions();

	for (auto it = cells->begin() + 1; it != cells->end(); it++) {
		auto fromPos = *it;
		auto toPos = *(it - 1);

		emit(events::snake::CellMovedEvent(toPos, fromPos));
	}
	emit(events::snake::SnakeMovedEvent());
}

snake::Snake::Snake(sf::Vector2i head)
{
	reset(head);
}

bool snake::Snake::move(sf::Vector2i dir, bool silent)
{
	_wasTeleported = false;
	_alreadyTeleported = false;

	if (increase(dir, 1, true)) {
		_emitMove();
		if (_increaseBuffer > 0) {
			_increaseBuffer--;
			emit(events::snake::CellAddedEvent(getTail()));
			emit(events::snake::SnakeLengthChangedEvent(getLength(true), getLength(true) - 1));
			return true;
		}
		decrease(1, true);
		return true;
	}
	return false;
}

bool snake::Snake::increase(sf::Vector2i dir, int amount, bool silent)
{
	if (amount <= 0) return false;

	if (amount > 1) _increaseBuffer += amount - 1;
	auto newHead = getHead() + dir;
	if (getLength() > 1 && newHead == *(_positions.begin() + 1)) {
		return false;
	}
	_positions.push_front(newHead);
	if (!silent) { 
		emit(events::snake::CellAddedEvent(newHead));
		emit(events::snake::SnakeLengthChangedEvent(getLength(true), getLength(true) - amount));
	};
	return true;
}

bool snake::Snake::increase(int amount, bool silent)
{
	if (amount <= 0) return false;
	_increaseBuffer += amount;
	if (!silent) {
		emit(events::snake::SnakeLengthChangedEvent(getLength(true), getLength(true) - amount));
	}
	return true;
}

bool snake::Snake::decrease(int amount, bool silent)
{
	if (getLength(true) <= amount) return false;
	auto startLength = getLength(true);

	_increaseBuffer -= amount;
	if (_increaseBuffer < 0) {
		amount = -_increaseBuffer;
		_increaseBuffer = 0;
	}
	/*if (_increaseBuffer >= amount) {
		_increaseBuffer -= amount;
		if (_increaseBuffer == 0) {
			emit(events::snake::SnakeLengthChangedEvent(getLength(true), getLength(true) + amount));
			return true;
		}
	}*/

	/*if (getLength() <= amount) {
		if (_increaseBuffer <= amount) return false;
		_increaseBuffer -= amount;
		emit(events::snake::SnakeLengthChangedEvent(getLength(true), getLength(true) + amount));
		return true;
	};*/

	for (int i = 0; i < amount; i++) {
		auto cell = getTail();
		_positions.pop_back();
		if (!silent) {
			emit(events::snake::CellRemovedEvent(cell));
		}
	}
	emit(events::snake::SnakeLengthChangedEvent(getLength(true), startLength));
	return true;
}

sf::Vector2i snake::Snake::getHead()
{
	return _positions.front();
}

sf::Vector2i snake::Snake::getTail()
{
	return _positions.back();
}

const std::deque<sf::Vector2i>* snake::Snake::getCellPositions()
{
	return &_positions;
}

bool snake::Snake::has(sf::Vector2i pos)
{
	return std::find(_positions.begin(), _positions.end(), pos) != _positions.end();
}

void snake::Snake::setSpeed(float speed)
{
	_speed = speed;
}

float snake::Snake::getSpeed()
{
	return _speed;
}

int snake::Snake::getLength(bool withBuffer)
{
	return _positions.size() + (withBuffer ? _increaseBuffer : 0);
}

bool snake::Snake::isDead()
{
	return _isDead;
}

bool snake::Snake::eat(cells::food::AppleCell* apple)
{
	auto dir = apple->getGridPosition() - getHead();
	if (abs(dir.x) > 1 || abs(dir.y) > 1) return false;
	increase(apple->getFoodAmount());
	emit(events::snake::AppleEatenEvent(apple->getGridPosition()));
	return true;
}

void snake::Snake::reset(sf::Vector2i head)
{
	_speed = 1;
	_increaseBuffer = 0;
	_isDead = false;
	_positions.clear();
	_positions.push_front(head);
}

void snake::Snake::die()
{
	_isDead = true;
	emit(events::snake::SnakeDiedEvent());
}

void snake::Snake::teleport(sf::Vector2i pos)
{
	auto wasTp = _wasTeleported;
	_wasTeleported = true;
	emit(events::snake::SnakeBeforeTeleportEvent(pos));

	if (!wasTp) {
		if (_alreadyTeleported) {
			_alreadyTeleported = false;
			return;
		}
		auto prevHead = getHead();
		_positions.push_front(pos);
		_emitMove();
		emit(events::snake::SnakeTeleportedEvent(pos, prevHead));

		if (_increaseBuffer > 0) {
			_increaseBuffer--;
			emit(events::snake::CellAddedEvent(getTail()));
			return;
		}
		decrease(1, true);
		return;
	}

	auto prevHead = getHead();
	_positions.pop_front();
	_positions.push_front(pos);
	emit(events::snake::CellMovedEvent(pos, prevHead));
	emit(events::snake::SnakeTeleportedEvent(pos, prevHead));
	_alreadyTeleported = true;
}
