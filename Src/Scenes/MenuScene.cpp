#include "MenuScene.h"

#include "../Util/ResourceManager.h"
#include "../GameConfig.h"

void scenes::MenuScene::init()
{
	auto form = new views::forms::FormView(sf::Vector2f());

	_background = new views::ui::SpriteView(sf::Vector2f(0, 0), TEXTURE_UI_MENU_BACKGROUND);
	_logo = new views::ui::SpriteView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 4), TEXTURE_UI_LOGO);
	_logo->align(views::CENTER_X | views::CENTER_Y);

	_startButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 2 + 100), L"Начать игру");
	_startButton->getTextComponent()->setCharacterSize(40);
	_startButton->align(views::CENTER_X | views::CENTER_Y);
	_topButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 2 + 160), L"Рекорды");
	_topButton->align(views::CENTER_X | views::CENTER_Y);
	_exitButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 2 + 210), L"Выход");
	_exitButton->align(views::CENTER_X | views::CENTER_Y);

	_eventIds[0] = _startButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::MenuScene::onStartButtonClicked, this, std::placeholders::_1));
	_eventIds[1] = _topButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::MenuScene::onTopButtonClicked, this, std::placeholders::_1));
	_eventIds[2] = _exitButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::MenuScene::onExitButtonClicked, this, std::placeholders::_1));

	form->add(_background);
	form->add(_logo);
	form->add(_startButton);
	form->add(_topButton);
	form->add(_exitButton);

	addView(form);
}

void scenes::MenuScene::onStartButtonClicked(const events::Event& e)
{
	exit(CODE_OPENGAMECFG);
}

void scenes::MenuScene::onTopButtonClicked(const events::Event& e)
{
	exit(CODE_OPENRATING);
}

void scenes::MenuScene::onExitButtonClicked(const events::Event& e)
{
	exit(CODE_EXIT);
}

scenes::MenuScene::MenuScene(util::NewCamera* camera) : Scene(camera)
{
	init();
	_camera->center();
}

scenes::MenuScene::~MenuScene()
{
	_exitButton->off<events::button::ButtonMouseUpEvent>(_eventIds[2]);
	_topButton->off<events::button::ButtonMouseUpEvent>(_eventIds[1]);
	_startButton->off<events::button::ButtonMouseUpEvent>(_eventIds[0]);
}
