#include "SpriteButtonView.h"

void views::ui::SpriteButtonView::setTexture(const char* id, sf::Color color)
{
	auto sprite = getSpriteComponent();
	sprite->setColor(color);
	_spriteView->setTextureId(id);

	auto bounds = sprite->getGlobalBounds();
	_bounds->setSize(sf::Vector2f(bounds.width, bounds.height));
}

void views::ui::SpriteButtonView::onHoverEnter()
{
	if (!_is_clicked)
		setTexture(_hoverTextureId, _hoverColor);
	emit(events::button::ButtonHoverEnterEvent());
}

void views::ui::SpriteButtonView::onHoverLeave()
{
	if (!_is_clicked) {
		setTexture(_primaryTextureId, _primaryColor);
	}
	emit(events::button::ButtonHoverLeaveEvent());
}

void views::ui::SpriteButtonView::onMouseDown()
{
	setTexture(_clickTextureId, _clickColor);
	emit(events::button::ButtonMouseDownEvent());
}

void views::ui::SpriteButtonView::onMouseUp(bool in_area)
{
	setTexture(_is_hovered ? _hoverTextureId : _primaryTextureId, _is_hovered ? _hoverColor : _primaryColor);
	if (in_area)
		emit(events::button::ButtonMouseUpEvent());
}

void views::ui::SpriteButtonView::_align(uint8_t alignment)
{
	_spriteView->align(alignment);
}

views::ui::SpriteButtonView::SpriteButtonView(sf::Vector2f pos) : ButtonView(pos)
{
	_spriteView = new views::ui::SpriteView(pos, nullptr);
	addView(_spriteView);
}

void views::ui::SpriteButtonView::setPrimaryTextureId(const char* id)
{
	_primaryTextureId = id;
	if (!_is_hovered && !_is_clicked) {
		setTexture(id, _primaryColor);
	}
}

void views::ui::SpriteButtonView::setHoverTextureId(const char* id)
{
	_hoverTextureId = id;
	if (_is_hovered && !_is_clicked) {
		setTexture(id, _hoverColor);
	}
}

void views::ui::SpriteButtonView::setClickTextureId(const char* id)
{
	_clickTextureId = id;
	if (_is_clicked) {
		setTexture(id, _clickColor);
	}
}

void views::ui::SpriteButtonView::setTextureId(const char* id)
{
	setPrimaryTextureId(id);
	setHoverTextureId(id);
	setClickTextureId(id);
}

void views::ui::SpriteButtonView::setPrimaryColor(sf::Color color)
{
	_primaryColor = color;
	if (!_is_hovered && !_is_clicked) {
		setTexture(_primaryTextureId, color);
	}
}

void views::ui::SpriteButtonView::setHoverColor(sf::Color color)
{
	_hoverColor = color;
	if (_is_hovered && !_is_clicked) {
		setTexture(_hoverTextureId, color);
	}
}

void views::ui::SpriteButtonView::setClickColor(sf::Color color)
{
	_clickColor = color;
	if (_is_clicked) {
		setTexture(_clickTextureId, color);
	}
}

void views::ui::SpriteButtonView::setPosition(sf::Vector2f pos)
{
	_bounds->setPosition(pos);
	_spriteView->setPosition(pos);
}

sf::Sprite* views::ui::SpriteButtonView::getSpriteComponent()
{
	return _spriteView->getSpriteComponent();
}
