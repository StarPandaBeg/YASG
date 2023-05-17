#include "MenuItemView.h"

#include "../../Util/ResourceManager.h"
#include <exception>

void views::ui::MenuItemView::onLeftButtonClick(const events::Event& e)
{
	left();
}

void views::ui::MenuItemView::onRightButtonClick(const events::Event& e)
{
	right();
}

views::ui::MenuItemView::MenuItemView(sf::Vector2f pos, float textWidth) : GroupView(pos)
{
	_leftButtonView = new SpriteButtonView(pos);
	_leftButtonView->setTextureId(TEXTURE_UI_BUTTON_LEFT);
	_leftButtonView->setHoverColor(sf::Color::White);
	_leftButtonView->setPrimaryColor(sf::Color(200, 200, 200));
	_leftButtonView->setClickColor(sf::Color(160, 160, 160));

	_labelTextView = new TextView(sf::Vector2f());
	_labelTextView->getTextComponent()->setCharacterSize(26);
	_labelTextView->align(views::CENTER_X);

	auto textBounds = _labelTextView->getBounds()->getGlobalBounds();
	auto rightBtnPos = sf::Vector2f(textBounds.left + textBounds.width + 10, pos.y);
	_rightButtonView = new SpriteButtonView(sf::Vector2f());
	_rightButtonView->setTextureId(TEXTURE_UI_BUTTON_RIGHT);
	_rightButtonView->setHoverColor(sf::Color::White);
	_rightButtonView->setPrimaryColor(sf::Color(200, 200, 200));
	_rightButtonView->setClickColor(sf::Color(160, 160, 160));
	setTextWidth(textWidth);

	_eventIds[0] = _leftButtonView->on<events::button::ButtonMouseUpEvent>(std::bind(&MenuItemView::onLeftButtonClick, this, std::placeholders::_1));
	_eventIds[1] = _rightButtonView->on<events::button::ButtonMouseUpEvent>(std::bind(&MenuItemView::onRightButtonClick, this, std::placeholders::_1));

	addView(_leftButtonView);
	addView(_labelTextView);
	addView(_rightButtonView);
}

views::ui::MenuItemView::~MenuItemView()
{
	_rightButtonView->off<events::button::ButtonMouseUpEvent>(_eventIds[1]);
	_leftButtonView->off<events::button::ButtonMouseUpEvent>(_eventIds[0]);
}

int views::ui::MenuItemView::addMenuItem(sf::String label)
{
	int id = _idIncr++;
	_variants.emplace(id, label);
	if (_currentVariantId == -1) select(id);
	return id;
}

void views::ui::MenuItemView::removeMenuItem(int id)
{
	// TODO
	throw std::logic_error("Not implemented");
}

void views::ui::MenuItemView::removeMenuItem(sf::String label)
{
	// TODO
	throw std::logic_error("Not implemented");
}

void views::ui::MenuItemView::setTextWidth(float textWidth)
{
	auto leftButtonBounds = _leftButtonView->getBounds()->getGlobalBounds();
	auto rightButtonPos = sf::Vector2f(leftButtonBounds.left + leftButtonBounds.width + textWidth, leftButtonBounds.top);
	_rightButtonView->setPosition(rightButtonPos);

	auto textOffset = sf::Vector2f(leftButtonBounds.width + textWidth / 2, 0);
	_labelTextView->setPosition(_leftButtonView->getPosition() + textOffset);
}

int views::ui::MenuItemView::getCurrentId()
{
	return _currentVariantId;
}

bool views::ui::MenuItemView::select(int id)
{
	if (id >= _variants.size()) return false;
	_currentVariantId = id;
	_labelTextView->setText(_variants[id]);
	emit(events::menu::MenuItemSelectedEvent(id));
	return true;
}

bool views::ui::MenuItemView::left()
{
	if (_variants.size() <= 1) return false;
	int id = _currentVariantId - 1 < 0 ? _variants.size() - 1 : _currentVariantId - 1;
	return select(id);
}

bool views::ui::MenuItemView::right()
{
	if (_variants.size() <= 1) return false;
	int id = _currentVariantId + 1 >= _variants.size() ? 0 : _currentVariantId + 1;
	return select(id);
}
