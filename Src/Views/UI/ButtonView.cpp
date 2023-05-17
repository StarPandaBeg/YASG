#include "ButtonView.h"

#include "../../Events/UIEventSystem.h"

void views::ui::ButtonView::onHoverEnter()
{
	emit(events::button::ButtonHoverEnterEvent());
}

void views::ui::ButtonView::onHoverLeave()
{
	emit(events::button::ButtonHoverLeaveEvent());
}

void views::ui::ButtonView::onMouseDown()
{
	emit(events::button::ButtonMouseDownEvent());
}

void views::ui::ButtonView::onMouseUp(bool in_area)
{
	if (in_area)
		emit(events::button::ButtonMouseUpEvent());
}

views::ui::ButtonView::ButtonView(sf::Vector2f pos) : GroupView(pos)
{
	_ids[0] = util::UIEventSystem::instance()->add(this);
}

views::ui::ButtonView::~ButtonView()
{
	util::UIEventSystem::instance()->remove(_ids[0]);
}

sf::FloatRect views::ui::ButtonView::getClickableArea()
{
	return _bounds->getGlobalBounds();
}

bool views::ui::ButtonView::isInteractable()
{
	return _enabled;
}

void views::ui::ButtonView::setHoverState(bool state)
{
	if (state == _is_hovered) return;
	_is_hovered = state;
	if (state) {
		onHoverEnter();
	}
	else {
		onHoverLeave();
	}
}

void views::ui::ButtonView::setClickState(bool state, bool in_area)
{
	if (state == _is_clicked) return;
	_is_clicked = state;
	if (state) {
		onMouseDown();
	}
	else {
		onMouseUp(in_area);
	}
}
