#pragma once

#include "IGridShape.h"

namespace grid {
	namespace shapes {
		class RhombusShape : public IGridShape
		{
		private:
			sf::Vector2i _size;
		public:
			RhombusShape(sf::Vector2i size) : _size(size) {}
			bool contains(sf::Vector2i point) override;
		};
	}
}



