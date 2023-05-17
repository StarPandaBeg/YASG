#include "DrawableRenderer.h"

void views::renderers::DrawableRenderer::render(sf::RenderWindow* window)
{
	window->draw(*_drawable);
}
