#pragma once

#include "FormView.h"

namespace views {
	namespace forms {
		class UIFormView : public FormView
		{
		public:
			UIFormView(sf::Vector2f pos);
			virtual int getOrderInLayer() override;
		};
	}
}

