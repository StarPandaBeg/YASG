#include "TextButtonView.h"

#include <iostream>

void views::ui::TextButtonView::onHoverEnter()
{
	if (!_is_clicked)
		getTextComponent()->setFillColor(_hoverColor);
	emit(events::button::ButtonHoverEnterEvent());
}

void views::ui::TextButtonView::onHoverLeave()
{
	if (!_is_clicked) {
		getTextComponent()->setFillColor(_primaryColor);
	}
	emit(events::button::ButtonHoverLeaveEvent());
}

void views::ui::TextButtonView::onMouseDown()
{
	getTextComponent()->setFillColor(_clickColor);
	emit(events::button::ButtonMouseDownEvent());
}

void views::ui::TextButtonView::onMouseUp(bool in_area)
{
	getTextComponent()->setFillColor(_is_hovered ? _hoverColor : _primaryColor);
	if (in_area)
		emit(events::button::ButtonMouseUpEvent());
}

void views::ui::TextButtonView::_align(uint8_t alignment)
{
	_textView->align(alignment);
}

views::ui::TextButtonView::TextButtonView(sf::Vector2f pos) : TextButtonView(pos, "") {}
views::ui::TextButtonView::TextButtonView(sf::Vector2f pos, sf::String text) : ButtonView(pos)
{
	_textView = new TextView(pos);
	_textView->getTextComponent()->setFillColor(_primaryColor);
	setText(text);
	addView(_textView);
}

void views::ui::TextButtonView::setPosition(sf::Vector2f pos)
{
	_textView->setPosition(pos);
}

sf::Vector2f views::ui::TextButtonView::getPosition()
{
	return _textView->getPosition();
}

void views::ui::TextButtonView::setPrimaryColor(sf::Color color)
{
	_primaryColor = color;
	if (!_is_hovered && !_is_clicked) {
		getTextComponent()->setFillColor(color);
	}
}

void views::ui::TextButtonView::setHoverColor(sf::Color color)
{
	_hoverColor = color;
	if (_is_hovered && !_is_clicked) {
		getTextComponent()->setFillColor(color);
	}
}

void views::ui::TextButtonView::setClickColor(sf::Color color)
{
	_clickColor = color;
	if (_is_clicked) {
		getTextComponent()->setFillColor(color);
	}
}

void views::ui::TextButtonView::setText(sf::String text)
{
	_textView->setText(text);
	auto bounds = _textView->getBounds();
	_bounds->setSize(bounds->getSize());
}

sf::Text* views::ui::TextButtonView::getTextComponent()
{
	return _textView->getTextComponent();
}