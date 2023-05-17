#pragma once

#include "Scene.h"
#include "../Views/Forms/FormView.h"
#include "../Views/UI/SpriteView.h"
#include "../Views/UI/TextButtonView.h"

namespace scenes {
	enum MenuSceneExitCode {
		CODE_OPENGAMECFG,
		CODE_OPENRATING,
		CODE_EXIT
	};
	class MenuScene : public Scene {
	private:
		views::ui::SpriteView* _background;
		views::ui::SpriteView* _logo;
		views::ui::TextButtonView* _startButton;
		views::ui::TextButtonView* _topButton;
		views::ui::TextButtonView* _exitButton;

		int _eventIds[3];

		void init();
		void onStartButtonClicked(const events::Event& e);
		void onTopButtonClicked(const events::Event& e);
		void onExitButtonClicked(const events::Event& e);
	public:
		MenuScene(util::NewCamera* camera);
		~MenuScene();
	};
}
