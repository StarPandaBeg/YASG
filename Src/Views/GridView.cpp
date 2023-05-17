#include "GridView.h"

#include "Renderers/GridViewRenderer.h"

views::GridView::GridView(grid::Grid* grid, sf::Vector2f pos) : views::View((sf::Vector2f)grid->getSize(), pos), _grid(grid) {
	_renderer = new renderers::GridViewRenderer(grid);
}

views::GridView::~GridView()
{
	delete _renderer;
}

views::renderers::ICustomRenderer* views::GridView::getCustomRenderer()
{
	return _renderer;
}