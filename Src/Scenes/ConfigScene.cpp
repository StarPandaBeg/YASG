#include "ConfigScene.h"

#include "../Util/ResourceManager.h"
#include "../GameConfig.h"
#include "../Grid/Shapes/IGridShape.h"
#include "../Grid/Shapes/HeartShape.h"
#include "../Grid/Shapes/EllipseShape.h"
#include "../Grid/Shapes/RhombusShape.h"

static const sf::Vector2i deskSizes[3] = {
	sf::Vector2i(32, 32),
	sf::Vector2i(64, 64),
	sf::Vector2i(100, 100),
};
static const int foodAmount[3][2] = {
		{
			1, 3
		},
		{
			1, 5
		},
		{
			1, 7
		},
};
static const int cratesAmount[3][3] = {
		{
			15, 30
		},
		{
			80, 120
		},
		{
			100, 150
		},
};

void initColumnRow(sf::Vector2f pos, sf::String label, std::vector<sf::String> items, views::ui::TextView** labelView, views::ui::MenuItemView** menuItemView)
{
	*labelView = new views::ui::TextView(pos);
	(*labelView)->setText(label);

	pos += sf::Vector2f(260, 5);
	*menuItemView = new views::ui::MenuItemView(pos);
	(*menuItemView)->setTextWidth(150);
	for (auto item : items) {
		(*menuItemView)->addMenuItem(item);
	}
}

void scenes::ConfigScene::init()
{
	_background = new views::ui::SpriteView(sf::Vector2f(0, 0), TEXTURE_UI_MENU_BACKGROUND);

	_headerTextView = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, 40));
	_headerTextView->getTextComponent()->setCharacterSize(40);
	_headerTextView->align(views::CENTER_X | views::CENTER_Y);
	_headerTextView->setText(L"Настройка игры");

	_startButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT - 150), L"Начать игру");
	_startButton->align(views::CENTER_X | views::CENTER_Y);
	_menuButton = new views::ui::TextButtonView(sf::Vector2f(CFG_WINDOW_WIDTH / 2, CFG_WINDOW_HEIGHT - 80), L"Назад");
	_menuButton->align(views::CENTER_X | views::CENTER_Y);

	_eventIds[9] = _startButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::ConfigScene::onPlayButton, this, std::placeholders::_1));
	_eventIds[10] = _menuButton->on<events::button::ButtonMouseUpEvent>(std::bind(&scenes::ConfigScene::onMenuButton, this, std::placeholders::_1));

	_playerNameLabel = new views::ui::TextView(sf::Vector2f(CFG_WINDOW_WIDTH / 2 + 110, CFG_WINDOW_HEIGHT / 2 + 60));
	_playerNameLabel->setText(L"Имя игрока:");
	_playerNameInput = new views::ui::TextInputView(sf::Vector2f(CFG_WINDOW_WIDTH / 2 + 370, CFG_WINDOW_HEIGHT / 2 + 60), 250, 16);
	_playerNameInput->setText("Player");

	addView(_background);
	addView(_headerTextView);
	addView(_startButton);
	addView(_menuButton);
	addView(_playerNameLabel);
	addView(_playerNameInput);

	initColumns();
}

void scenes::ConfigScene::initColumns()
{
	std::vector<sf::String> labels = {
		L"Размер поля:",
		L"Форма:",
		L"Беск. поле:",
		L"Кол-во еды:",
		L"Разные фрукты:",
		L"Откусить хвост:",

		L"Дерев. ящики:",
		L"Железн. ящики:",
		L"Порталы:",
	};
	std::vector<std::vector<sf::String>> items = {
		{
			L"маленькое",
			L"среднее",
			L"большое"
		},
		{
			L"поле",
			L"сердце",
			L"круг",
			L"ромб",
		},
		{
			L"да",
			L"нет"
		},
		{
			L"мало",
			L"много"
		},
		{
			L"да",
			L"нет"
		},
		{
			L"да",
			L"нет"
		},
		{
			L"нет",
			L"мало",
			L"много",
		},
		{
			L"нет",
			L"мало",
			L"много",
		},
		{
			L"да",
			L"нет"
		},
	};
	std::vector<std::pair<views::ui::TextView**, views::ui::MenuItemView**>> views = {
		{
			&_deskSizeLabel,
			&_deskSizeMenu
		},
		{
			&_deskShapeLabel,
			&_deskShapeMenu
		},
		{
			&_infiniteDeskLabel,
			&_infiniteDeskMenu
		},
		{
			&_foodAmountLabel,
			&_foodAmountMenu
		},
		{
			&_differentFoodLabel,
			&_differentFoodMenu
		},
		{
			&_tailCutLabel,
			&_tailCutMenu
		},
		{
			&_woodenCratesLabel,
			&_woodenCratesMenu
		},
		{
			&_ironCratesLabel,
			&_ironCratesMenu
		},
		{
			&_portalsLabel,
			&_portalsMenu
		},
	};

	auto pos = sf::Vector2f(110, CFG_WINDOW_HEIGHT / 2 - 240);
	for (int i = 0; i < labels.size(); i++) {
		initColumnRow(pos, labels[i], items[i], views[i].first, views[i].second);
		addView(*views[i].first);
		addView(*views[i].second);

		_eventIds[i] = (*views[i].second)->on<events::menu::MenuItemSelectedEvent>(std::bind(&scenes::ConfigScene::onMenuItemSelected, this, std::placeholders::_1));

		pos.y += 60;
		if (i % 5 == 0 && i > 0) {
			pos.x += CFG_WINDOW_WIDTH / 2;
			pos.y = CFG_WINDOW_HEIGHT / 2 - 240;
		}
	}
}

void scenes::ConfigScene::initConfigState()
{
	auto cfg = getConfig();

	// Desk size
	auto currentSize = cfg.getDeskCellAmount();
	auto foundSize = std::find(std::begin(deskSizes), std::end(deskSizes), currentSize);
	int sizeIndex = 0;
	if (foundSize != std::end(deskSizes)) {
		sizeIndex = std::distance(std::begin(deskSizes), foundSize);
		_deskSizeMenu->select(sizeIndex);
	}
	else {
		_cfg.setDeskSize(deskSizes[sizeIndex]);
		_deskSizeMenu->select(sizeIndex);
	}
	
	// Food amount
	auto currentFoodAmount = cfg.getMaxFoodAmount();
	auto foundFoodAmount = std::find(std::begin(foodAmount[sizeIndex]), std::end(foodAmount[sizeIndex]), currentFoodAmount);
	if (foundFoodAmount != std::end(foodAmount[sizeIndex])) {
		_foodAmountMenu->select(std::distance(std::begin(foodAmount[sizeIndex]), foundFoodAmount));
	}
	else {
		_cfg.setMaxFoodAmount(foodAmount[sizeIndex][0]);
		_foodAmountMenu->select(0);
	}

	// shape
	// TODO

	// Wood crates
	if (!cfg.allowWoodCrates()) {
		_woodenCratesMenu->select(0);
	}
	else {
		auto currentWoodenCratesValue = cfg.getWoodCrateAmount();
		auto woodenCratesFound = std::find(std::begin(cratesAmount[sizeIndex]), std::end(cratesAmount[sizeIndex]), currentWoodenCratesValue);
		if (woodenCratesFound != std::end(cratesAmount[sizeIndex])) {
			_woodenCratesMenu->select(std::distance(std::begin(cratesAmount[sizeIndex]), woodenCratesFound) + 1);
		}
		else {
			_cfg.setWoodCratesAmount(cratesAmount[sizeIndex][0]);
			_woodenCratesMenu->select(1);
		}
	}

	// Iron crates
	if (!cfg.allowIronCrates()) {
		_ironCratesMenu->select(0);
	}
	else {
		auto currentIronCratesValue = cfg.getWoodCrateAmount();
		auto ironCratesFound = std::find(std::begin(cratesAmount[sizeIndex]), std::end(cratesAmount[sizeIndex]), currentIronCratesValue);
		if (ironCratesFound != std::end(cratesAmount[sizeIndex])) {
			_ironCratesMenu->select(std::distance(std::begin(cratesAmount[sizeIndex]), ironCratesFound) + 1);
		}
		else {
			_cfg.setIronCratesAmount(cratesAmount[sizeIndex][0]);
			_ironCratesMenu->select(1);
		}
	}

	_infiniteDeskMenu->select(cfg.dieOnBorderTouch());
	_differentFoodMenu->select(!cfg.allowDifferentFruits());
	_tailCutMenu->select(cfg.dieOnSelfTouch());
	_portalsMenu->select(cfg.allowPortals());
}

void scenes::ConfigScene::uiToConfig()
{
	
	auto currentDeskSizeId = _deskSizeMenu->getCurrentId();
	_cfg.setDeskSize(deskSizes[currentDeskSizeId]);
	
	_cfg.allowInfinityDesk(!_infiniteDeskMenu->getCurrentId());
	_cfg.setMaxFoodAmount(foodAmount[currentDeskSizeId][_foodAmountMenu->getCurrentId()]);
	_cfg.allowDifferentFruits(!_differentFoodMenu->getCurrentId());
	_cfg.allowTailCut(!_tailCutMenu->getCurrentId());
	
	_cfg.allowWoodCrates(_woodenCratesMenu->getCurrentId() != 0);
	if (_woodenCratesMenu->getCurrentId() > 0) _cfg.setWoodCratesAmount(cratesAmount[currentDeskSizeId][_woodenCratesMenu->getCurrentId() - 1]);
	_cfg.allowIronCrates(_ironCratesMenu->getCurrentId() != 0);
	if (_ironCratesMenu->getCurrentId() > 0) _cfg.setIronCratesAmount(cratesAmount[currentDeskSizeId][_ironCratesMenu->getCurrentId() - 1]);
	_cfg.allowPortals(!_portalsMenu->getCurrentId());

	switch (_deskShapeMenu->getCurrentId())
	{
		case 0:
			_cfg.setShape(nullptr);
			break;
		case 1:
			_cfg.setShape(new grid::shapes::HeartShape(deskSizes[currentDeskSizeId]));
			break;
		case 2:
			_cfg.setShape(new grid::shapes::EllipseShape(deskSizes[currentDeskSizeId]));
			break;
		case 3:
			_cfg.setShape(new grid::shapes::RhombusShape(deskSizes[currentDeskSizeId]));
			break;
	}
}

void scenes::ConfigScene::onMenuItemSelected(const events::Event& e)
{
	uiToConfig();
}

void scenes::ConfigScene::onMenuButton(const events::Event& e)
{
	exit(CODE_MENU);
}

void scenes::ConfigScene::onPlayButton(const events::Event& e)
{
	auto playerName = _playerNameInput->getTextComponent()->getString();
	if (playerName.getSize() == 0) return;
	_cfg.setPlayerName(playerName);

	exit(CODE_STARTGAME);
}

scenes::ConfigScene::ConfigScene(util::NewCamera* camera, GameConfig initialCfg) : Scene(camera)
{
	init();
	camera->center();
	_cfg = GameConfigBuilder(initialCfg);
	initConfigState();
}

scenes::ConfigScene::~ConfigScene()
{
	_menuButton->off<events::button::ButtonMouseUpEvent>(_eventIds[10]);
	_startButton->off<events::button::ButtonMouseUpEvent>(_eventIds[9]);

	_portalsMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[8]);
	_ironCratesMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[7]);
	_woodenCratesMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[6]);
	_tailCutMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[5]);
	_differentFoodMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[4]);
	_foodAmountMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[3]);
	_infiniteDeskMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[2]);
	_deskShapeMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[1]);
	_deskSizeMenu->off<events::menu::MenuItemSelectedEvent>(_eventIds[0]);
}

GameConfig scenes::ConfigScene::getConfig()
{
	return _cfg.build();
}
