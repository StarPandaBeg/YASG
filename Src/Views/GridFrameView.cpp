#include "GridFrameView.h"

#include "Renderers/DrawableRenderer.h"
#include "../Drawable/GridFrame.h"

void views::GridFrameView::onShapeChanged(const events::Event& e)
{
	_tilemap->recalculate();
}

views::GridFrameView::GridFrameView(grid::Grid* grid, sf::Vector2f pos) : View(pos), _grid(grid)
{
	_tilemap = new drawable::GridFrame(grid);
	_renderer = new renderers::DrawableRenderer(_tilemap);
	_eventIds[0] = _grid->on<events::grid::ShapeChangedEvent>(std::bind(&views::GridFrameView::onShapeChanged, this, std::placeholders::_1));
}

views::GridFrameView::~GridFrameView()
{
	_grid->off<events::grid::ShapeChangedEvent>(_eventIds[0]);
	delete _renderer;
	delete _tilemap;
}

views::renderers::ICustomRenderer* views::GridFrameView::getCustomRenderer()
{
	return _renderer;
}

