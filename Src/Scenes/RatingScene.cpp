#include "RatingScene.h"

#include "../Util/ResourceManager.h"
#include "../Util/Utility.h"
#include "../GameConfig.h"
#include <sstream>
#include <iomanip>

void scenes::RatingScene::init()
{
	_form = new views::forms::FormView(sf::Vector2f());

	_background = new views::ui::SpriteView(sf::Vector2f(0, 0), TEXTURE_UI_MENU_BACKGROUND);
	_headerTextView = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, 40));
	_headerTextView->getTextComponent()->setCharacterSize(40);
	_headerTextView->align(views::CENTER_X | views::CENTER_Y);
	_headerTextView->setText(L"Таблица рекордов");
	_backButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT - 80), L"Назад");
	_backButton->align(views::CENTER_X | views::CENTER_Y);

	_eventIds[0] = _backButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::RatingScene::onBackButtonClicked, this, std::placeholders::_1));

	_form->add(_background);
	_form->add(_headerTextView);
	_form->add(_backButton);
	addView(_form);
}

void scenes::RatingScene::onBackButtonClicked(const events::Event& e)
{
	exit();
}

void scenes::RatingScene::generateTable()
{
	auto scoreTable = util::HighScoreManager::instance()->get();
	if (scoreTable.size() == 0) return;

	int i = 1;
	for (auto scoreRow : scoreTable) {
		addRow(i++, scoreRow, sf::Vector2f(CFG_WINDOW_WIDTH / 2 - 418, CFG_WINDOW_HEIGHT / 4 - 60 + 40 * (i - 1)));
	}
}

void scenes::RatingScene::addRow(int i, util::ScoreRow row, sf::Vector2f pos)
{
	auto playerName = util::Utility::truncate(row.playerName, 30);
	auto timeStr = util::Utility::toTimeString(sf::seconds(row.time));

	auto indexTextView = new views::ui::TextView(pos);
	indexTextView->setText(std::to_string(i));
	
	auto usernameTextView = new views::ui::TextView(pos + sf::Vector2f(60, 0));
	usernameTextView->setText(playerName);

	auto scoreTextView = new views::ui::TextView(pos + sf::Vector2f(620, 0));
	scoreTextView->align(views::RIGHT);
	scoreTextView->setText(std::to_string(row.score));

	auto timeTextView = new views::ui::TextView(pos + sf::Vector2f(760, 0));
	timeTextView->align(views::RIGHT);
	timeTextView->setText(timeStr);

	sf::FloatRect bounds = timeTextView->getTextComponent()->getLocalBounds();
	sf::Vector2f size(bounds.left * 2 + bounds.width, bounds.top * 2 + bounds.height);

	_form->add(indexTextView);
	_form->add(usernameTextView);
	_form->add(scoreTextView);
	_form->add(timeTextView);
}

scenes::RatingScene::RatingScene(util::NewCamera* camera) : Scene(camera)
{
	init();
	generateTable();
	camera->center();
}

scenes::RatingScene::~RatingScene()
{
	_backButton->off<events::button::ButtonMouseUpEvent>(_eventIds[0]);
}
