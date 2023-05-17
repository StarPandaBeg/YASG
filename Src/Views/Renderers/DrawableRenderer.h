#pragma once

#include "ICustomRenderer.h"
#include "SFML/Graphics.hpp"

namespace views {
	namespace renderers {
		class DrawableRenderer : public ICustomRenderer
		{
		private:
			sf::Drawable* _drawable;
		public:
			DrawableRenderer(sf::Drawable* drawable) : _drawable(drawable) {}
			virtual void render(sf::RenderWindow* window) override;
		};
	}
}

