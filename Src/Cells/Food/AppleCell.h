#pragma once

#include "../Cell.h"
#include "../../Commands/IHitCommand.h"
#include "../../Util/ResourceManager.h"
#include "IEatable.h"

namespace commands {
	class IHitCommand;
}

namespace cells {
	class Cell;

	namespace food {
		class IEatable;

		class AppleCell : public cells::Cell, public IEatable
		{
		private:
			int _foodAmount = 1;
			inline static std::vector<const char*> _textures{
				TEXTURE_APPLE,
				TEXTURE_CHERRY,
				TEXTURE_BANANA
			};
		public:
			AppleCell(sf::Vector2i position) : cells::Cell(position) {}
			commands::IHitCommand* onCollisionWith(cells::Cell* cell) override;
			const char* getTextureId() override;

			virtual int getFoodAmount() override;
			void setFoodAmount(int foodAmount);
		};
	}
}