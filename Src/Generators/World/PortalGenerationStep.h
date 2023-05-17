#pragma once

#include <vector>
#include "IGenerationStep.h"

namespace generators {
	namespace world {
		class PortalGenerationStep : public IGenerationStep
		{
		private:
			bool step(grid::Grid* grid);
			sf::Vector2i getFreePosition(grid::Grid* grid);

			std::vector<sf::Color> _colors {
				sf::Color::Red,
				sf::Color::Cyan,
				sf::Color::Yellow
			};
			int _index = 0;
		public:
			PortalGenerationStep() {}
			virtual void process(grid::Grid* grid) override;
		};
	}
}

