#pragma once

#include "SFML/Graphics.hpp"
#include "../Events/Event.h"
#include "../Events/EventDispatcher.h"
#include <queue>

namespace cells {
	namespace food {
		class AppleCell;
	}
}

namespace events {
	namespace snake {
		struct CellEvent : Event {
			sf::Vector2i position;
			CellEvent(sf::Vector2i pos) : position(pos) {};
		};

		struct CellAddedEvent : CellEvent {
			CellAddedEvent(sf::Vector2i pos) : CellEvent(pos) {};
		};

		struct CellRemovedEvent : CellEvent {
			CellRemovedEvent(sf::Vector2i pos) : CellEvent(pos) {};
		};

		struct CellMovedEvent : CellEvent {
			sf::Vector2i sourcePosition;
			CellMovedEvent(sf::Vector2i pos, sf::Vector2i source) : CellEvent(pos), sourcePosition(source) {}
		};

		struct SnakeBeforeTeleportEvent : CellEvent {
			SnakeBeforeTeleportEvent(sf::Vector2i pos) : CellEvent(pos) {};
		};
		struct SnakeTeleportedEvent : CellEvent {
			sf::Vector2i from;
			SnakeTeleportedEvent(sf::Vector2i pos, sf::Vector2i from) : CellEvent(pos), from(from) {};
		};
		struct SnakeMovedEvent : Event {};
		struct SnakeLengthChangedEvent : Event {
			int from;
			int to;
			SnakeLengthChangedEvent(int to, int from) : to(to), from(from) {}
		};
		struct SnakeDiedEvent : Event {};

		struct AppleEatenEvent : CellEvent {
			AppleEatenEvent(sf::Vector2i pos) : CellEvent(pos) {};
		};
	}
}

namespace snake {
	class Snake : public events::EventDispatcher
	{
	private:
		int _increaseBuffer = 0;
		std::deque<sf::Vector2i> _positions;
		float _speed = 1;
		bool _isDead = false;
		bool _wasTeleported = false;
		bool _alreadyTeleported = false;
		void _emitMove();
	public:
		Snake(sf::Vector2i head);
		bool move(sf::Vector2i dir, bool silent = false);
		bool increase(sf::Vector2i dir, int amount = 1, bool silent = false);
		bool increase(int amount = 1, bool silent = false);
		bool decrease(int amount = 1, bool silent = false);
		bool has(sf::Vector2i pos);
		void setSpeed(float speed);
		bool eat(cells::food::AppleCell* apple);
		void reset(sf::Vector2i head);
		void die();
		void teleport(sf::Vector2i pos);

		sf::Vector2i getHead();
		sf::Vector2i getTail();
		const std::deque<sf::Vector2i>* getCellPositions();
		float getSpeed();
		int getLength(bool withBuffer = false);
		bool isDead();
	};
}
