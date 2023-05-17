#pragma once

#include "IGridShape.h"

namespace grid {
	namespace shapes {
		class HeartShape : public IGridShape
		{
			sf::Vector2i _size;
		public:
			HeartShape(sf::Vector2i size) : _size(size) {}
			virtual bool contains(sf::Vector2i point) override;
		};
	}
}
