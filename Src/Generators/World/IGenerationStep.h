#pragma once

#include "../../Grid/Grid.h"
#include <random>

namespace generators {
	namespace world {
		class IGenerationStep
		{
		protected:
			std::default_random_engine _rnd;

			sf::Vector2i getRandomPosition(sf::Vector2i max)
			{
				return sf::Vector2i(
					_rnd() % max.x,
					_rnd() % max.y
				);
			}
		public:
			virtual void process(grid::Grid* grid) = 0;
			virtual void setSeed(int seed) { _rnd.seed(seed); }
		};
	}
}
