#pragma once

#include "IGenerationStep.h"

namespace generators {
	namespace world {
		class CrateGenerationStep : public IGenerationStep
		{
		private:
			int _crateAmount;
			bool _destructable;

			bool step(grid::Grid* grid);
		public:
			CrateGenerationStep(int crateAmount, bool destructable = true) : _crateAmount(crateAmount), _destructable(destructable) {}
			virtual void process(grid::Grid* grid) override;
		};
	}
}
