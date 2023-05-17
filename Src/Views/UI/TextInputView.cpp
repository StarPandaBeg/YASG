#include "TextInputView.h"

#include "../../Util/ResourceManager.h"
#include "../../Events/UIEventSystem.h"
#include <iostream>

views::ui::TextInputView::TextInputView(sf::Vector2f pos, float width, int charAmount) : GroupView(pos)
{
	_textView = new TextView(pos);
	_charAmount = charAmount;

	auto underlinePos = pos + sf::Vector2f(0, 40);
	auto underlineSize = sf::Vector2f(width, 3);
	_underlineRectangleView = new RectangleView(underlinePos, underlineSize);
	_underlineRectangleView->setTextureId(TEXTURE_EMPTY);
	setActive(false);

	_eventIds[0] = util::UIEventSystem::instance()->add(this);

	addView(_textView);
	addView(_underlineRectangleView);
}

views::ui::TextInputView::~TextInputView()
{
	util::UIEventSystem::instance()->remove(_eventIds[0]);
}

sf::FloatRect views::ui::TextInputView::getClickableArea()
{
	auto pos = _textView->getPosition();
	auto size = _underlineRectangleView->getBounds()->getSize() + sf::Vector2f(0, 40);
	return sf::FloatRect(pos, size);
}

bool views::ui::TextInputView::isInteractable()
{
	return _enabled;
}

void views::ui::TextInputView::setClickState(bool state, bool in_area)
{
	if (state && in_area) setActive(true);
	else if (!in_area) setActive(false);
}

void views::ui::TextInputView::onKeyEnter(char key)
{
	if (!_active) return;
	auto text = _textView->getTextComponent()->getString();
	auto textSize = text.getSize();
	if (key == 8) {
		if (textSize == 0) return;
		text.erase(textSize-1);
	}
	else {
		if (textSize >= _charAmount) return;

		// 0..9, A..Z, a..z, _
		if (!((key > 47 && key < 58) || (key > 64 && key < 91) || (key > 96 && key < 123) || (key == 95))) return;
		text += static_cast<char>(key);
	}
	_textView->setText(text);
}

void views::ui::TextInputView::setActive(bool state)
{
	_active = state;

	auto color = state ? sf::Color::White : sf::Color(200, 200, 200);
	_underlineRectangleView->setColor(color);
	_textView->setColor(color);
}

void views::ui::TextInputView::setTextWidth(float width)
{
	_underlineRectangleView->getBounds()->setSize(sf::Vector2f(width, 3));
}

void views::ui::TextInputView::setCharacterAmount(int value)
{
	_charAmount = value;
}

void views::ui::TextInputView::setText(sf::String text)
{
	_textView->setText(text);
}

sf::Text* views::ui::TextInputView::getTextComponent()
{
	return _textView->getTextComponent();
}
