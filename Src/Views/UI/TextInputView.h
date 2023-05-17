#pragma once

#include "../GroupView.h"
#include "TextView.h"
#include "../RectangleView.h"
#include "IInteractable.h"

namespace views {
	namespace ui {
		class TextInputView : public GroupView, public IInteractable
		{
		private:
			TextView* _textView;
			RectangleView* _underlineRectangleView;

			bool _active = false;
			int _charAmount;

			int _eventIds[1];
		public:
			TextInputView(sf::Vector2f pos, float width = 200, int charAmount = 16);
			~TextInputView();

			virtual sf::FloatRect getClickableArea() override;
			virtual bool isInteractable() override;
			virtual void setClickState(bool state, bool in_area = true) override;
			virtual void onKeyEnter(char key) override;

			void setActive(bool state);
			void setTextWidth(float width);
			void setCharacterAmount(int value);
			void setText(sf::String text);
			
			sf::Text* getTextComponent();
		};
	}
}
