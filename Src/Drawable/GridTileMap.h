#pragma once

#include "TiledDrawable.h"

namespace drawable {
	class GridTileMap : public TiledDrawable
	{
	public:
		GridTileMap(grid::Grid* grid);
		void recalculate() override;
	};
}

