#pragma once

#include "ICustomRenderer.h"
#include "../View.h"
#include <map>

namespace views {
	namespace renderers {
		class GroupRenderer : public ICustomRenderer
		{
		private:
			std::multimap<int, views::ViewObj>* _map;
			bool _ignoreView = false;
		public:
			GroupRenderer(std::multimap<int, views::ViewObj>* map);
			virtual void render(sf::RenderWindow* win) override;
			void setIgnoreView(bool ignoreView);
		};
	}
}

