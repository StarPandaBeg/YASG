#pragma once

#include "ICustomRenderer.h"
#include "../../Grid/Grid.h"

namespace views {
	namespace renderers {
		class GridViewRenderer : public ICustomRenderer
		{
		private:
			grid::Grid* _grid;
		public:
			GridViewRenderer(grid::Grid* grid) : _grid(grid) {}
			virtual void render(sf::RenderWindow* win) override;
		};
	}
}
