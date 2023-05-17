#pragma once

#include "SFML/Graphics.hpp"
#include "../Grid/Grid.h"

namespace drawable {
	class TiledDrawable : public sf::Drawable, public sf::Transformable {
	protected:
		grid::Grid* _grid;
		sf::Texture* _texture = nullptr;
		sf::VertexArray _vertices;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void createQuad(sf::Vertex* quad, sf::Vector2i tileSize, sf::Vector2i pos);
	public:
		TiledDrawable(grid::Grid* grid) : _grid(grid) {}
		virtual void recalculate() = 0;
	};
}