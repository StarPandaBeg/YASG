#pragma once

#include "View.h"
#include "../Grid/Grid.h"
#include "../Drawable/TiledDrawable.h"

namespace views {
	class GridFrameView : public View
	{
	private:
		grid::Grid* _grid;
		drawable::TiledDrawable* _tilemap;
		renderers::ICustomRenderer* _renderer;
		int _eventIds[1];

		void onShapeChanged(const events::Event& e);
	public:
		GridFrameView(grid::Grid* grid, sf::Vector2f pos);
		~GridFrameView();

		renderers::ICustomRenderer* getCustomRenderer();
		int getOrderInLayer() override { return LAYER_GRIDFRAME; }
	};
}

