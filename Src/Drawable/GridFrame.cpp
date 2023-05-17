#include "GridFrame.h"

#include "../Util/ResourceManager.h"
#include "../GameConfig.h"

bool checkNeighbours(sf::Vector2i pos, grid::Grid* grid) {
	if (grid->contains(pos + sf::Vector2i(1, 0))) return true;
	if (grid->contains(pos + sf::Vector2i(-1, 0))) return true;
	if (grid->contains(pos + sf::Vector2i(0, 1))) return true;
	if (grid->contains(pos + sf::Vector2i(0, -1))) return true;
	return false;
}

drawable::GridFrame::GridFrame(grid::Grid* grid) : TiledDrawable(grid)
{
	_texture = util::ResourceManager::instance()->getTexture(TEXTURE_GRASS);
	recalculate();
}

void drawable::GridFrame::recalculate() {
	auto size = _grid->getSize();
	auto tileSize = sf::Vector2i(CFG_CELL_WIDTH, CFG_CELL_HEIGHT);

	_vertices.clear();
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(size.x * size.y * 4);

	for (int i = -1, k = 0; i <= size.x; ++i) {
		for (int j = -1; j <= size.y; ++j)
		{
			auto pos = sf::Vector2i(i, j);

			if (_grid->contains(pos)) continue;
			if (!checkNeighbours(pos, _grid)) continue;

			sf::Vertex* quad = &_vertices[k += 4];
			createQuad(quad, tileSize, pos);
		}
	}
}