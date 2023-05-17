#pragma once

#include "ButtonView.h"
#include "TextView.h"

namespace views {
	namespace ui {
		class TextButtonView : public ButtonView
		{
		private:
			TextView* _textView;

			sf::Color _primaryColor = sf::Color(200, 200, 200);
			sf::Color _hoverColor = sf::Color(255, 255, 255);
			sf::Color _clickColor = sf::Color(160, 160, 160);
		protected:
			virtual void onHoverEnter() override;
			virtual void onHoverLeave() override;
			virtual void onMouseDown() override;
			virtual void onMouseUp(bool in_area) override;

			void _align(uint8_t alignment) override;
		public:
			TextButtonView(sf::Vector2f pos);
			TextButtonView(sf::Vector2f pos, sf::String text);

			virtual void setPosition(sf::Vector2f pos) override;
			virtual sf::Vector2f getPosition() override;

			void setPrimaryColor(sf::Color color);
			void setHoverColor(sf::Color color);
			void setClickColor(sf::Color color);

			void setText(sf::String text);
			sf::Text* getTextComponent();
		};
	}
}
