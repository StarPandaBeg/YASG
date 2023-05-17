#include "TextView.h"

#include "../Renderers/DrawableRenderer.h"
#include "../../Util/ResourceManager.h"

views::ui::TextView::TextView(sf::Vector2f pos) : View(pos)
{
	_text->setPosition(pos);
	_renderer = new renderers::DrawableRenderer(_text);

	auto font = util::ResourceManager::instance()->getFont(FONT_PRICEDOWN);
	_text->setFont(*font);
	setText("");
}

views::ui::TextView::~TextView()
{
	delete _text;
	delete _renderer;
}

views::renderers::ICustomRenderer* views::ui::TextView::getCustomRenderer()
{
	return _renderer;
}

void views::ui::TextView::setText(const sf::String& text)
{
	_text->setString(text);
	_align(_lastAlignment);

	sf::FloatRect bounds = _text->getLocalBounds();
	sf::Vector2f size(bounds.left * 2 + bounds.width, bounds.top * 2 + bounds.height);
	_bounds->setSize(size);
}

void views::ui::TextView::_align(uint8_t alignment)
{
	views::View::align(_text, _text->getLocalBounds(), alignment);
}

void views::ui::TextView::setPosition(sf::Vector2f pos)
{
	_text->setPosition(pos);
}

sf::Vector2f views::ui::TextView::getPosition()
{
	return _text->getPosition();
}

sf::Text* views::ui::TextView::getTextComponent()
{
	return _text;
}
