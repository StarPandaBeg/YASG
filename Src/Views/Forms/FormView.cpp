#include "FormView.h"

views::forms::FormView::FormView(sf::Vector2f pos) : GroupView(pos)
{
}

int views::forms::FormView::add(views::View* v)
{
	return addView(v);
}

views::View* views::forms::FormView::remove(int id)
{
	return removeView(id);
}
