#pragma once

#include "ButtonView.h"
#include "SpriteView.h"

namespace views {
	namespace ui {
		class SpriteButtonView : public ButtonView
		{
		private:
			SpriteView* _spriteView;

			const char* _primaryTextureId = nullptr;
			const char* _hoverTextureId = nullptr;
			const char* _clickTextureId = nullptr;

			sf::Color _primaryColor = sf::Color(255, 255, 255);
			sf::Color _hoverColor = sf::Color(255, 255, 255);
			sf::Color _clickColor = sf::Color(255, 255, 255);

			void setTexture(const char* id, sf::Color color);
		protected:
			virtual void onHoverEnter() override;
			virtual void onHoverLeave() override;
			virtual void onMouseDown() override;
			virtual void onMouseUp(bool in_area) override;

			void _align(uint8_t alignment) override;
		public:
			SpriteButtonView(sf::Vector2f pos);

			void setPrimaryTextureId(const char* id);
			void setHoverTextureId(const char* id);
			void setClickTextureId(const char* id);
			void setTextureId(const char* id);

			void setPrimaryColor(sf::Color color);
			void setHoverColor(sf::Color color);
			void setClickColor(sf::Color color);

			void setPosition(sf::Vector2f pos) override;

			sf::Sprite* getSpriteComponent();
		};
	}
}

