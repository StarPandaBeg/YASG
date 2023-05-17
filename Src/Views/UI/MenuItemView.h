#pragma once

#include "../GroupView.h"
#include "TextView.h"
#include "SpriteButtonView.h"
#include <map>

namespace events {
	namespace menu {
		struct MenuItemSelectedEvent : public Event {
			int id;
			MenuItemSelectedEvent(int id) : id(id) {}
		};
	}
}

namespace views {
	namespace ui {
		class MenuItemView : public GroupView, public events::EventDispatcher
		{
		private:
			std::map<int, sf::String> _variants;
			int _currentVariantId = -1;
			int _idIncr = 0;

			SpriteButtonView* _leftButtonView;
			SpriteButtonView* _rightButtonView;
			TextView* _labelTextView;

			int _eventIds[2];

			void onLeftButtonClick(const events::Event& e);
			void onRightButtonClick(const events::Event& e);
		public:
			MenuItemView(sf::Vector2f pos, float textWidth = 80);
			~MenuItemView();

			int addMenuItem(sf::String label);
			void removeMenuItem(int id);
			void removeMenuItem(sf::String label);

			void setTextWidth(float textWidth);

			int getCurrentId();
			bool select(int id);
			bool left();
			bool right();
		};
	}
}

