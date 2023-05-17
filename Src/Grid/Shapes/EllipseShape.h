#pragma once

#include "IGridShape.h"

namespace grid {
	namespace shapes {
		class EllipseShape : public IGridShape
		{
		private:
			sf::Vector2i _size;
		public:
			EllipseShape(sf::Vector2i size) : _size(size) {}
			bool contains(sf::Vector2i point) override;
		};
	}
}



