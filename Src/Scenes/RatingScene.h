#pragma once

#include "Scene.h"
#include "../Views/Forms/FormView.h"
#include "../Views/UI/SpriteView.h"
#include "../Views/UI/TextView.h"
#include "../Views/UI/TextButtonView.h"
#include "../Util/HighScoreManager.h"

namespace scenes {
	class RatingScene : public Scene
	{
	private:
		views::ui::SpriteView* _background;
		views::ui::TextView* _headerTextView;
		views::ui::TextButtonView* _backButton;
		views::forms::FormView* _form;

		int _eventIds[1];
		void init();
		void onBackButtonClicked(const events::Event& e);

		void generateTable();
		void addRow(int i, util::ScoreRow row, sf::Vector2f pos);
	public:
		RatingScene(util::NewCamera* camera);
		~RatingScene();
	};
}

