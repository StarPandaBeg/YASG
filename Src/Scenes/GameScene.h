#pragma once

#include "Scene.h"
#include "../Views/RectangleView.h"
#include "../SnakeGame.h"
#include "../Views/GridView.h"
#include "../Views/GridTileMapView.h"
#include "../Views/GridFrameView.h"
#include "../Views/Forms/FormView.h"
#include "../Views/UI/TextView.h"
#include "../Views/UI/SpriteView.h"
#include "../Views/UI/TextButtonView.h"

namespace scenes {
	enum GameSceneExitCode {
		CODE_MENUBTN
	};

	class GameScene : public Scene
	{
	private:
		views::GridView* _gridView;
		views::GridTileMapView* _gridTileMapView;
		views::GridFrameView* _gridFrameView;
		views::ui::TextView* _scoreTextView;
		views::ui::TextView* _clockTextView;
		views::ui::SpriteView* _clockSpriteView;
		views::ui::TextView* _pauseTextView;
		views::ui::TextButtonView* _pauseButton;
		views::ui::TextButtonView* _pauseResumeButton;
		views::ui::TextButtonView* _pauseMenuButton;
		views::ui::TextView* _gameoverTextView;
		views::ui::TextView* _gameoverScoreTextView;
		views::ui::TextView* _gameoverTimeTextView;
		views::ui::TextButtonView* _gameoverReplayButton;
		views::ui::TextButtonView* _gameoverMenuButton;

		views::forms::FormView* _pauseFormView;
		views::forms::FormView* _gameOverFormView;
		
		SnakeGame* _game;

		int _eventIds[9];
		void onScoreUpdate(const events::Event& e);
		void onClockUpdate(const events::Event& e);
		void onPause(const events::Event& e);
		void onGameOver(const events::Event& e);
		void onPauseButtonClicked(const events::Event& e);
		void onResumeButtonClicked(const events::Event& e);
		void onMenuButtonClicked(const events::Event& e);
		void onReplayButtonClicked(const events::Event& e);
		views::RectangleView* createDeskBackground();

		void initGameForm();
		void initGui();
		void initPausedOverlay();
		void initGameOverOverlay();
	public:
		GameScene(util::NewCamera* camera, SnakeGame* game);
		~GameScene();
	};
}
