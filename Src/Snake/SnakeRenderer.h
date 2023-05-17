#pragma once

#include "Snake.h"
#include "../Grid/Grid.h"

namespace snake {
	class SnakeRenderer
	{
	private:
		snake::Snake* _snake;
		grid::Grid* _grid;

		int _ids[3];

		void onCellAdded(const events::Event& e);
		void onCellRemoved(const events::Event& e);
		void onCellMoved(const events::Event& e);
	public:
		SnakeRenderer(snake::Snake* snake, grid::Grid* grid);
		~SnakeRenderer();
		void reset();
	};
}
