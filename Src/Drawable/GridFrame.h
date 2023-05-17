#pragma once

#include "TiledDrawable.h"

namespace drawable {
	class GridFrame : public TiledDrawable
	{
	public:
		GridFrame(grid::Grid* grid);
		void recalculate() override;
	};
}



