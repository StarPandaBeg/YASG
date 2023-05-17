#pragma once

#include "../GroupView.h"

namespace views {
	namespace forms {
		class FormView : public GroupView
		{
		public:
			FormView(sf::Vector2f pos);
			int add(views::View* v);
			views::View* remove(int id);
		};
	}
}

