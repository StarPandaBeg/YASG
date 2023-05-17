#pragma once

#include "../View.h"

namespace views {
	namespace ui {
		class SpriteView : public View
		{
		private:
			const char* _spriteId;
			void _align(uint8_t alignment) override;
		public:
			SpriteView(sf::Vector2f pos, const char* spriteId);
			sf::Sprite* getSpriteComponent();
		};
	}
}

