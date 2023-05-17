#include "SpriteView.h"

views::ui::SpriteView::SpriteView(sf::Vector2f pos, const char* spriteId) : View(pos)
{
	_spriteId = spriteId;
	setTextureId(spriteId);
}

void views::ui::SpriteView::_align(uint8_t alignment)
{
	View::align(_defaultSprite, _defaultSprite->getLocalBounds(), alignment);
}

sf::Sprite* views::ui::SpriteView::getSpriteComponent()
{
	return _defaultSprite;
}
