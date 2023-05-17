#include "View.h"

#include "../Util/ResourceManager.h"
#include <iostream>

void views::View::recreateSpriteTexture(const char* id)
{
	if (id == nullptr) {
		return;
	}
	auto texture = util::ResourceManager::instance()->getTexture(id);
	_defaultSprite->setTexture(*texture);
}

void views::View::align(sf::Transformable* obj, sf::FloatRect bounds, uint8_t alignment)
{
	auto horizontal = alignment & 0b11;
	auto vertical = alignment & (0b11 << 2);

	auto x = 0;
	auto y = 0;
	if (horizontal > LEFT) {
		x = (horizontal == CENTER_X) ? (bounds.left + bounds.width / 2.0f) : (bounds.width - 1);
	}
	if (vertical > TOP) {
		y = (vertical == CENTER_Y) ? (bounds.top + bounds.height / 2.0f) : (bounds.height - 1);
	}
	obj->setOrigin(x, y);
}

void views::View::_align(uint8_t alignment)
{
	align(_defaultSprite, _defaultSprite->getLocalBounds(), alignment);
}

views::View::View(sf::Vector2f position, sf::Vector2f size)
{
	_bounds = new sf::RectangleShape(size);
	setPosition(position);
	_defaultSprite->setTextureRect(sf::IntRect(sf::Vector2i(), (sf::Vector2i)_bounds->getSize()));
}

views::View::~View()
{
	delete _defaultSprite;
	delete _bounds;
}

void views::View::setPosition(sf::Vector2f pos)
{
	_bounds->setPosition(pos);
	_defaultSprite->setPosition(pos);
}

sf::Vector2f views::View::getPosition()
{
	return _bounds->getPosition();
}

void views::View::align(uint8_t alignment)
{
	align(_bounds, _bounds->getLocalBounds(), alignment);
	_align(alignment);
	_lastAlignment = alignment;
}

sf::RectangleShape* views::View::getBounds()
{
	return _bounds;
}

void views::View::setTextureId(const char* id)
{
	_textureId = id;
	recreateSpriteTexture(id);
}

void views::View::setColor(sf::Color c)
{
	_defaultSprite->setColor(c);
}

int views::View::getOrderInLayer()
{
	return LAYER_DEFAULT;
}

bool views::View::isEnabled()
{
	return _enabled;
}

void views::View::setEnabled(bool enabled)
{
	_enabled = enabled;
}

void views::View::render(sf::RenderWindow* window) {
	if (!_enabled) return;
	auto customRenderer = getCustomRenderer();
	if (customRenderer != nullptr) return customRenderer->render(window);

	auto textureId = getTextureId();
	if (textureId == nullptr) return;

	if (textureId != _oldTextureId) {
		_oldTextureId = (char*)textureId;
		recreateSpriteTexture(_oldTextureId);
	}
	window->draw(*_defaultSprite);
}
