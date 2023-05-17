#pragma once

#include "Scene.h"
#include "../Views/Forms/FormView.h"
#include "../Views/UI/SpriteView.h"
#include "../Views/UI/TextButtonView.h"
#include "../Views/UI/MenuItemView.h"
#include "../Views/UI/TextInputView.h"
#include "../GameConfig.h"
#include "../SnakeGame.h"

namespace scenes {
	enum ConfigSceneExitCode {
		CODE_STARTGAME,
		CODE_MENU
	};
	class ConfigScene : public Scene
	{
	private:
		views::ui::SpriteView* _background;
		views::ui::TextView* _headerTextView;
		views::ui::TextButtonView* _startButton;
		views::ui::TextButtonView* _menuButton;

		views::ui::TextView* _deskSizeLabel;
		views::ui::MenuItemView* _deskSizeMenu;
		views::ui::TextView* _deskShapeLabel;
		views::ui::MenuItemView* _deskShapeMenu;
		views::ui::TextView* _infiniteDeskLabel;
		views::ui::MenuItemView* _infiniteDeskMenu;
		views::ui::TextView* _foodAmountLabel;
		views::ui::MenuItemView* _foodAmountMenu;
		views::ui::TextView* _differentFoodLabel;
		views::ui::MenuItemView* _differentFoodMenu;
		views::ui::TextView* _tailCutLabel;
		views::ui::MenuItemView* _tailCutMenu;
		views::ui::TextView* _woodenCratesLabel;
		views::ui::MenuItemView* _woodenCratesMenu;
		views::ui::TextView* _ironCratesLabel;
		views::ui::MenuItemView* _ironCratesMenu;
		views::ui::TextView* _portalsLabel;
		views::ui::MenuItemView* _portalsMenu;
		views::ui::TextView* _playerNameLabel;
		views::ui::TextInputView* _playerNameInput;

		GameConfigBuilder _cfg;
		int _eventIds[11];

		void init();
		void initColumns();

		void initConfigState();
		void uiToConfig();
		void onMenuItemSelected(const events::Event& e);
		void onMenuButton(const events::Event& e);
		void onPlayButton(const events::Event& e);
	public:
		ConfigScene(util::NewCamera* camera, GameConfig initialCfg = GameConfig());
		~ConfigScene();

		GameConfig getConfig();
	};
}

