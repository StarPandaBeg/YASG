#pragma once

#include "../Util/ITickable.h"
#include "Snake.h"
#include "../Grid/Grid.h"
#include "../Events/Event.h"

namespace snake {
	class SnakePhysics : public util::ITickable
	{
	private:
		sf::Vector2i _currentDirection = sf::Vector2i(0, 0);
		sf::Vector2i _nextDirection = sf::Vector2i(0, 0);

		bool _canMove = false;
		snake::Snake* _snake;
		grid::Grid* _grid;
		int _eventIds[2];

		void movementTick();
		bool canMoveTo(sf::Vector2i pos);
		bool onCollisionWith(cells::Cell* cell);
		bool onCollisionWithBorder(sf::Vector2i pos);

		void onSnakeBeforeTeleport(const events::Event& e);
		void onSnakeTeleport(const events::Event& e);
	public:
		SnakePhysics(snake::Snake* snake, grid::Grid* grid);
		~SnakePhysics();
		void tick() override;

		void setNextDirection(sf::Vector2i dir);
		sf::Vector2i getCurrentDirrection();
		void reset();
	};
}
