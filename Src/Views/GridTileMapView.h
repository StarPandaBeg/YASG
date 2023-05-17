#pragma once

#include "View.h"
#include "../Grid/Grid.h"
#include "../Drawable/TiledDrawable.h"

namespace views {
	class GridTileMapView : public View
	{
	private:
		grid::Grid* _grid;
		drawable::TiledDrawable* _tilemap;
		renderers::ICustomRenderer* _renderer;
		int _eventIds[1];

		void onShapeChanged(const events::Event& e);
	public:
		GridTileMapView(grid::Grid* grid, sf::Vector2f pos);
		~GridTileMapView();

		renderers::ICustomRenderer* getCustomRenderer();
		int getOrderInLayer() override { return LAYER_GRID; }
	};
}

