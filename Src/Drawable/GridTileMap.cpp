#include "GridTileMap.h"

#include "../Util/ResourceManager.h"
#include "../GameConfig.h"

drawable::GridTileMap::GridTileMap(grid::Grid* grid) : TiledDrawable(grid) 
{
	_texture = util::ResourceManager::instance()->getTexture(TEXTURE_DESK);
	recalculate();
}

void drawable::GridTileMap::recalculate() {
	auto size = _grid->getSize();
	auto tileSize = sf::Vector2i(CFG_CELL_WIDTH, CFG_CELL_HEIGHT);

	_vertices.clear();
	_vertices.setPrimitiveType(sf::Quads);
	_vertices.resize(size.x * size.y * 4);

	for (int i = 0; i < size.x; ++i) {
		for (int j = 0; j < size.y; ++j)
		{
			auto pos = sf::Vector2i(i, j);

			if (!_grid->contains(pos)) continue;

			sf::Vertex* quad = &_vertices[(i + j * size.x) * 4];
			createQuad(quad, tileSize, pos);
		}
	}
}