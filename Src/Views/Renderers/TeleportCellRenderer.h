#pragma once

#include "ICustomRenderer.h"

#include "SFML/Graphics.hpp"

namespace views {
	namespace renderers {
		class TeleportCellRenderer : public ICustomRenderer
		{
		private:
			sf::Sprite _baseSprite;
			sf::Sprite _glowSprite;
			sf::Color _color;
			sf::Vector2f _position;
		public:
			TeleportCellRenderer(sf::Vector2f pos, sf::Color color);
			virtual void render(sf::RenderWindow* win) override;
			void setColor(sf::Color c);
		};
	}
}


