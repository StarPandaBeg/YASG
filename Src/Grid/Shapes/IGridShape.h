#pragma once

#include "SFML/Graphics.hpp"

namespace grid {
	namespace shapes {
		class IGridShape
		{
		public:
			virtual bool contains(sf::Vector2i point) = 0;
		};
	}
}
