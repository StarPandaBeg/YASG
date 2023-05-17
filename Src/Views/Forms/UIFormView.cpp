#include "UIFormView.h"

#include "../Renderers/GroupRenderer.h"

views::forms::UIFormView::UIFormView(sf::Vector2f pos) : FormView(pos)
{
	auto groupRenderer = static_cast<renderers::GroupRenderer*>(_renderer);
	groupRenderer->setIgnoreView(true);
}

int views::forms::UIFormView::getOrderInLayer()
{
	return LAYER_GUI;
}
