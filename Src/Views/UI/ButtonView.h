#pragma once

#include "../GroupView.h"
#include "IInteractable.h"
#include "../../Events/Event.h"
#include "../../Events/EventDispatcher.h"

namespace events {
	namespace button {
		struct ButtonMouseDownEvent : events::Event {};
		struct ButtonMouseUpEvent : events::Event {};
		struct ButtonHoverEnterEvent : events::Event {};
		struct ButtonHoverLeaveEvent : events::Event {};
	}
}

namespace views {
	namespace ui {
		class ButtonView : public GroupView, public IInteractable, public events::EventDispatcher
		{
		private:
			int _ids[1];
		protected:
			bool _is_hovered = false;
			bool _is_clicked = false;

			virtual void onHoverEnter();
			virtual void onHoverLeave();
			virtual void onMouseDown();
			virtual void onMouseUp(bool in_area);
		public:
			ButtonView(sf::Vector2f pos);
			virtual ~ButtonView();

			virtual sf::FloatRect getClickableArea() override;
			virtual bool isInteractable() override;
			void setHoverState(bool state) override;
			void setClickState(bool state, bool in_area = true) override;
		};
	}
}

