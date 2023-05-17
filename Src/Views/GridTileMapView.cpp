#include "GridTileMapView.h"

#include "Renderers/DrawableRenderer.h"
#include "../Drawable/GridTileMap.h"

void views::GridTileMapView::onShapeChanged(const events::Event& e)
{
	_tilemap->recalculate();
}

views::GridTileMapView::GridTileMapView(grid::Grid* grid, sf::Vector2f pos) : View(pos), _grid(grid)
{
	_tilemap = new drawable::GridTileMap(grid);
	_renderer = new renderers::DrawableRenderer(_tilemap);
	_eventIds[0] = _grid->on<events::grid::ShapeChangedEvent>(std::bind(&views::GridTileMapView::onShapeChanged, this, std::placeholders::_1));
}

views::GridTileMapView::~GridTileMapView()
{
	_grid->off<events::grid::ShapeChangedEvent>(_eventIds[0]);
	delete _renderer;
	delete _tilemap;
}

views::renderers::ICustomRenderer* views::GridTileMapView::getCustomRenderer()
{
	return _renderer;
}

