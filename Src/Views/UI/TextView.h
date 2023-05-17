#pragma once

#include "../View.h"

namespace views {
	namespace ui {
		class TextView : public View
		{
		private:
			sf::Text* _text = new sf::Text();
			renderers::ICustomRenderer* _renderer;
			void _align(uint8_t alignment) override;
		public:
			TextView(sf::Vector2f pos);
			~TextView();
			renderers::ICustomRenderer* getCustomRenderer();
			void setText(const sf::String& text);
			void setPosition(sf::Vector2f pos) override;
			sf::Vector2f getPosition() override;
			sf::Text* getTextComponent();
		};
	}
}

