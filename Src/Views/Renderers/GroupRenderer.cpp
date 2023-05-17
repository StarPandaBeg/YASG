#include "GroupRenderer.h"

views::renderers::GroupRenderer::GroupRenderer(std::multimap<int, views::ViewObj>* map) : _map(map)
{
}

void views::renderers::GroupRenderer::render(sf::RenderWindow* win)
{
	auto ignoreView = _ignoreView;
	auto view = win->getView();

	if (ignoreView) win->setView(win->getDefaultView());
	for (auto const& v : *_map) {
		v.second.v->render(win);
	}
	if (ignoreView) win->setView(view);
}

void views::renderers::GroupRenderer::setIgnoreView(bool ignoreView)
{
	_ignoreView = ignoreView;
}
