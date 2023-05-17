#pragma once

#include "View.h"
#include "../Grid/Grid.h"

#include "SFML/Graphics.hpp"

namespace views {
	class GridView : public View
	{
	private:
		grid::Grid* _grid;
		renderers::ICustomRenderer* _renderer;
	public:
		GridView(grid::Grid* grid, sf::Vector2f pos);
		~GridView();

		renderers::ICustomRenderer* getCustomRenderer();
		int getOrderInLayer() override { return LAYER_GRID; }
	};
}
