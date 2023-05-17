#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Mouse.hpp"

namespace views {
	namespace ui {
		class IInteractable {
		public:
			virtual sf::FloatRect getClickableArea() = 0;
			virtual bool isInteractable() { return true; }
			virtual void setHoverState(bool state) {}
			virtual void setClickState(bool state, bool in_area = true) {}
			virtual void onKeyEnter(char key) {}
		};
	}
}