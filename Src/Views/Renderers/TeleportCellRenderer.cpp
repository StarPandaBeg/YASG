#include "TeleportCellRenderer.h"

#include "../../Util/ResourceManager.h"

views::renderers::TeleportCellRenderer::TeleportCellRenderer(sf::Vector2f pos, sf::Color color) : _color(color), _position(pos)
{
	auto baseTexture = util::ResourceManager::instance()->getTexture(TEXTURE_PORTAL_BASE);
	auto glowTexture = util::ResourceManager::instance()->getTexture(TEXTURE_PORTAL_GLOW);

	_baseSprite.setTexture(*baseTexture);
	_glowSprite.setTexture(*glowTexture);
	_baseSprite.setPosition(pos);
	_glowSprite.setPosition(pos);

	_baseSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	_glowSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

	_glowSprite.setColor(_color);
}

void views::renderers::TeleportCellRenderer::render(sf::RenderWindow* win)
{
	win->draw(_baseSprite);
	win->draw(_glowSprite);
}

void views::renderers::TeleportCellRenderer::setColor(sf::Color c)
{
	_color = c;
	_glowSprite.setColor(c);
}
