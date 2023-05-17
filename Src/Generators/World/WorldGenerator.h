#pragma once

#include <vector>
#include "IGenerationStep.h"
#include "../../Grid/Grid.h"
#include "../../GameConfig.h"

namespace generators {
	namespace world {
		class WorldGenerator
		{
		private:
			std::vector<IGenerationStep*> _steps;
			int _seed = 0;
		public:
			~WorldGenerator();
			void add(IGenerationStep* step);
			void run(grid::Grid* grid);
			void setSeed(int seed);

			static WorldGenerator* fromConfig(GameConfig cfg);
		};
	}
}

