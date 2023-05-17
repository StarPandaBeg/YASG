#pragma once

#include "SFML/Window/Event.hpp"

namespace util {
	class IWindowEventTickable
	{
	public:
		virtual void tick(sf::Event e) = 0;
	};
}

