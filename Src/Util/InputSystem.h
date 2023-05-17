#pragma once

#include "../Events/Event.h"
#include "../Events/EventDispatcher.h"

#include "SFML/Graphics.hpp"

namespace events {
	namespace input {
		enum class MovementDirection {
			UP,
			LEFT,
			DOWN,
			RIGHT
		};

		struct MouseEvent : Event {
			sf::Event::MouseButtonEvent e;
			MouseEvent(sf::Event::MouseButtonEvent e) : e(e) {};
		};

		struct KeyEvent : Event {
			sf::Event::KeyEvent e;
			KeyEvent(sf::Event::KeyEvent e) : e(e) {};
		};

		struct MovementEvent : Event {
			MovementDirection direction;
			MovementEvent(MovementDirection dir) : direction(dir) {};
		};
	}
}

namespace util {
	class InputSystem : public events::EventDispatcher
	{
	private:
		InputSystem() {};
	public:
		static InputSystem* instance();
		void update(sf::Event e);
	};
}

