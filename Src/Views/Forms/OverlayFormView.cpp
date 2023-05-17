#include "OverlayFormView.h"

#include "../RectangleView.h"
#include "../../GameConfig.h"
#include "../../Util/ResourceManager.h"

views::forms::OverlayFormView::OverlayFormView(sf::Vector2f pos) : UIFormView(pos)
{
	auto background = new RectangleView(sf::Vector2f(), sf::Vector2f(CFG_WINDOW_WIDTH, CFG_WINDOW_HEIGHT));
	background->setTextureId(TEXTURE_EMPTY);
	background->setColor(sf::Color(0, 0, 0, 200));
	addView(background);
}
