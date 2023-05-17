#include "GameScene.h"

#include "../Util/ResourceManager.h"
#include "../Views/Forms/UIFormView.h"
#include "../Views/Forms/OverlayFormView.h"
#include "../Views/GridView.h"
#include "../Util/Utility.h"

sf::Vector2i grid_mid(grid::Grid* grid) {
	return sf::Vector2i(
		grid->getSize().x / 2,
		grid->getSize().y / 2
	);
}

void scenes::GameScene::onScoreUpdate(const events::Event& e)
{
	auto ev = static_cast<const events::game::ScoreUpdateEvent&>(e);
	_scoreTextView->setText(std::to_string(ev.value));
}

void scenes::GameScene::onClockUpdate(const events::Event& e)
{
	auto ev = static_cast<const events::game::ClockUpdateEvent&>(e);
	auto timeString = util::Utility::toTimeString(ev.time);
	_clockTextView->setText(timeString);
}

void scenes::GameScene::onPause(const events::Event& e)
{
	auto ev = static_cast<const events::game::GamePausedEvent&>(e);
	_pauseFormView->setEnabled(ev.state);
}

void scenes::GameScene::onGameOver(const events::Event& e)
{
	auto timeString = util::Utility::toTimeString(_game->getTime());
	auto scoreText = L"Счёт: " + std::to_wstring(_game->getScore());
	auto timeText = sf::String(L"Время: ");
	timeText += timeString;

	_gameoverScoreTextView->setText(scoreText);
	_gameoverTimeTextView->setText(timeText);
	_gameOverFormView->setEnabled(true);
}

void scenes::GameScene::onPauseButtonClicked(const events::Event& e)
{
	_game->setPaused(true);
}

void scenes::GameScene::onResumeButtonClicked(const events::Event& e)
{
	_game->setPaused(false);
}

void scenes::GameScene::onMenuButtonClicked(const events::Event& e)
{
	_camera->setTarget(nullptr);
	exit(CODE_MENUBTN);
}

void scenes::GameScene::onReplayButtonClicked(const events::Event& e)
{
	_game->reset();

	auto snakeHeadPosition = _game->getSnake()->getHead();
	auto snakeHead = _game->getGrid()->get(snakeHeadPosition);
	_camera->setTarget(snakeHead);

	_gameOverFormView->setEnabled(false);
	_game->run();
}

views::RectangleView* scenes::GameScene::createDeskBackground()
{
	auto deskSize = _game->getConfig().getDeskSize();
	auto pos = (sf::Vector2f)(-deskSize * 2);
	auto size = (sf::Vector2f)(deskSize * 4);
	auto rect = new views::RectangleView(pos, size);
	rect->setTextureId((char*)TEXTURE_GRASS);
	return rect;
}

void scenes::GameScene::initGameForm()
{
	_gridView = new views::GridView(_game->getGrid(), sf::Vector2f());
	_gridTileMapView = new views::GridTileMapView(_game->getGrid(), sf::Vector2f());
	_gridFrameView = new views::GridFrameView(_game->getGrid(), sf::Vector2f());
	_eventIds[0] = _game->on<events::game::ScoreUpdateEvent>(std::bind(&scenes::GameScene::onScoreUpdate, this, std::placeholders::_1));
	_eventIds[1] = _game->on<events::game::ClockUpdateEvent>(std::bind(&scenes::GameScene::onClockUpdate, this, std::placeholders::_1));
	_eventIds[2] = _game->on<events::game::GamePausedEvent>(std::bind(&scenes::GameScene::onPause, this, std::placeholders::_1));
	_eventIds[3] = _game->on<events::game::GameOverEvent>(std::bind(&scenes::GameScene::onGameOver, this, std::placeholders::_1));

	auto form = new views::forms::FormView(sf::Vector2f());
	form->add(createDeskBackground());
	form->add(_gridTileMapView);
	form->add(_gridView);
	form->add(_gridFrameView);
	addView(form);
}

void scenes::GameScene::initGui()
{
	_scoreTextView = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, 40));
	_scoreTextView->align(views::CENTER_X | views::CENTER_Y);
	_clockTextView = new views::ui::TextView(sf::Vector2f(62, 40));
	_clockTextView->align(views::CENTER_Y);
	_clockSpriteView = new views::ui::SpriteView(sf::Vector2f(20, 40), TEXTURE_UI_CLOCK);
	_clockSpriteView->align(views::CENTER_Y);

	_pauseButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH - 20, 40), L"Пауза");
	_pauseButton->align(views::RIGHT | views::CENTER_Y);
	_eventIds[8] = _pauseButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::GameScene::onPauseButtonClicked, this, std::placeholders::_1));

	auto form = new views::forms::UIFormView(sf::Vector2f());
	form->add(_scoreTextView);
	form->add(_clockTextView);
	form->add(_clockSpriteView);
	form->add(_pauseButton);
	addView(form);
}

void scenes::GameScene::initPausedOverlay()
{
	_pauseFormView = new views::forms::OverlayFormView(sf::Vector2f());

	_pauseTextView = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, 40));
	_pauseTextView->getTextComponent()->setCharacterSize(40);
	_pauseTextView->align(views::CENTER_X | views::CENTER_Y);
	_pauseTextView->setText(L"Пауза");

	_pauseResumeButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 2), L"Продолжить");
	_pauseResumeButton->align(views::CENTER_X | views::CENTER_Y);
	_pauseMenuButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 2 + 60), L"Меню");
	_pauseMenuButton->align(views::CENTER_X | views::CENTER_Y);

	_pauseFormView->add(_pauseTextView);
	_pauseFormView->add(_pauseResumeButton);
	_pauseFormView->add(_pauseMenuButton);

	_eventIds[4] = _pauseResumeButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::GameScene::onResumeButtonClicked, this, std::placeholders::_1));
	_eventIds[5] = _pauseMenuButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::GameScene::onMenuButtonClicked, this, std::placeholders::_1));

	_pauseFormView->setEnabled(false);
	addView(_pauseFormView);
}

void scenes::GameScene::initGameOverOverlay()
{
	_gameOverFormView = new views::forms::OverlayFormView(sf::Vector2f());

	_gameoverTextView = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 4));
	_gameoverTextView->getTextComponent()->setCharacterSize(40);
	_gameoverTextView->align(views::CENTER_X | views::CENTER_Y);
	_gameoverTextView->setText(L"Вы проиграли! :(");

	_gameoverScoreTextView = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 4 + 70));
	_gameoverScoreTextView->getTextComponent()->setCharacterSize(24);
	_gameoverScoreTextView->getTextComponent()->setFillColor(sf::Color(200, 200, 200));
	_gameoverScoreTextView->align(views::CENTER_X | views::CENTER_Y);
	_gameoverTimeTextView = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 4 + 100));
	_gameoverTimeTextView->getTextComponent()->setCharacterSize(24);
	_gameoverTimeTextView->getTextComponent()->setFillColor(sf::Color(200, 200, 200));
	_gameoverTimeTextView->align(views::CENTER_X | views::CENTER_Y);

	_gameoverReplayButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 2), L"Переиграть");
	_gameoverReplayButton->align(views::CENTER_X | views::CENTER_Y);
	_gameoverMenuButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT / 2 + 60), L"Меню");
	_gameoverMenuButton->align(views::CENTER_X | views::CENTER_Y);

	_gameOverFormView->add(_gameoverTextView);
	_gameOverFormView->add(_gameoverScoreTextView);
	_gameOverFormView->add(_gameoverTimeTextView);
	_gameOverFormView->add(_gameoverReplayButton);
	_gameOverFormView->add(_gameoverMenuButton);

	_eventIds[6] = _gameoverReplayButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::GameScene::onReplayButtonClicked, this, std::placeholders::_1));
	_eventIds[7] = _gameoverMenuButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::GameScene::onMenuButtonClicked, this, std::placeholders::_1));

	_gameOverFormView->setEnabled(false);
	addView(_gameOverFormView);
}

scenes::GameScene::GameScene(util::NewCamera* camera, SnakeGame* game) : Scene(camera)
{
	_game = game;
	initGameForm();
	initGui();
	initPausedOverlay();
	initGameOverOverlay();

	auto snakeHeadPosition = _game->getSnake()->getHead();
	auto snakeHead = _game->getGrid()->get(snakeHeadPosition);
	_camera->setTarget(snakeHead);
}

scenes::GameScene::~GameScene()
{
	_pauseButton->off<events::button::ButtonMouseUpEvent>(_eventIds[8]);
	_gameoverMenuButton->off<events::button::ButtonMouseUpEvent>(_eventIds[7]);
	_gameoverReplayButton->off<events::button::ButtonMouseUpEvent>(_eventIds[6]);
	_pauseMenuButton->off<events::button::ButtonMouseUpEvent>(_eventIds[5]);
	_pauseResumeButton->off<events::button::ButtonMouseUpEvent>(_eventIds[4]);
	_game->off<events::game::GameOverEvent>(_eventIds[3]);
	_game->off<events::game::GamePausedEvent>(_eventIds[2]);
	_game->off<events::game::ClockUpdateEvent>(_eventIds[1]);
	_game->off<events::game::ScoreUpdateEvent>(_eventIds[0]);
}
