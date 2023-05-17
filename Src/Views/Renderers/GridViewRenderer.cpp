#include "GridViewRenderer.h"

void views::renderers::GridViewRenderer::render(sf::RenderWindow* win)
{
	std::lock_guard<std::mutex> gridLock{_grid->lock};
	auto cells = _grid->getCells();
	std::multimap<int, cells::Cell*> _ordered;

	for (auto it = cells->begin(); it != cells->end(); it++) {
		int zIndex = it->second->getOrderInLayer();
		auto cell = it->second;
		_ordered.emplace(zIndex, cell);
	}

	for (auto const& v : _ordered) {
		v.second->render(win);
	}
}
