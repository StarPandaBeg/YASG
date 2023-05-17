#pragma once

#include "View.h"

namespace views {
	class RectangleView :
		public View
	{
	public:
		RectangleView(sf::Vector2f pos, sf::Vector2f size) : View(pos, size) {};
	};
}
