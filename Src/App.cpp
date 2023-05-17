#include "App.h"

#include "Scenes/GameScene.h"
#include "Scenes/MenuScene.h"
#include "Scenes/RatingScene.h"
#include "Scenes/ConfigScene.h"
#include "GameConfig.h"
#include "Util/GameTimer.h"
#include "Util/ResourceManager.h"
#include "Util/HighScoreManager.h"

#include <thread>

util::NewCamera* App::createCamera()
{
	return new util::NewCamera(_renderWindow->getView());
}

void App::onWindowClose(const events::Event& e)
{
	util::GameTimer::Default->stop();
}

void App::onSceneExit(const events::Event& e)
{
	auto ev = static_cast<const events::scene::SceneExitEvent&>(e);
	switch (_state) {
		case MAIN_MENU :
			if (ev.code == scenes::CODE_EXIT) {
				App::exit();
			}
			if (ev.code == scenes::CODE_OPENGAMECFG) {
				_state = CONFIG;
				auto oldConfig = _game == nullptr ? GameConfig() : _game->getConfig();
				loadScene(new scenes::ConfigScene(_camera, oldConfig));
			}
			if (ev.code == scenes::CODE_OPENRATING) {
				_state = RATING;
				loadScene(new scenes::RatingScene(_camera));
			}
			break;
		case GAME :
			if (ev.code == scenes::GameSceneExitCode::CODE_MENUBTN) {
				_state = MAIN_MENU;
				_game->stop();
				loadScene(new scenes::MenuScene(_camera));
			}
			break;
		case RATING :
			_state = MAIN_MENU;
			loadScene(new scenes::MenuScene(_camera));
			break;
		case CONFIG : 
			if (ev.code == scenes::ConfigSceneExitCode::CODE_STARTGAME) {
				auto scene = static_cast<scenes::ConfigScene*>(_scene);
				delete _game;

				_state = GAME;
				_game = new SnakeGame(scene->getConfig());
				loadScene(new scenes::GameScene(_camera, _game));
				_game->run();
			}
			if (ev.code == scenes::ConfigSceneExitCode::CODE_MENU) {
				_state = MAIN_MENU;
				loadScene(new scenes::MenuScene(_camera));
			}
			break;
	}
}

void App::loadScene(scenes::Scene* s)
{
	if (_scene != nullptr) {
		_scene->off<events::scene::SceneExitEvent>(_eventIds[1]);
	}
	_scene = s;
	_eventIds[1] = _scene->on<events::scene::SceneExitEvent>(std::bind(&App::onSceneExit, this, std::placeholders::_1));
	_window->setScene(_scene);
}

App::~App() {
	if (_scene != nullptr) _scene->off<events::scene::SceneExitEvent>(_eventIds[1]);
	_window->off<events::window::WindowCloseEvent>(_eventIds[0]);

	delete _game;
	delete _camera;
	delete _window;
}

App::App(sf::RenderWindow* window)
{
	util::ResourceManager::instance()->load();
	util::HighScoreManager::instance()->load();

	_renderWindow = window;
	_window = new Window();
	_camera = createCamera();

	_eventIds[0] = _window->on<events::window::WindowCloseEvent>(std::bind(&App::onWindowClose, this, std::placeholders::_1));

	_window->setRenderWindow(_renderWindow);
	_window->setMainCamera(_camera);

	// _game = new SnakeGame(GameConfig());
	loadScene(new scenes::MenuScene(_camera));
}

void App::run()
{
	std::thread rendering_thread(&Window::display, _window);
	std::thread gametimer_thread(&util::GameTimer::run, util::GameTimer::Default);

	_window->run();
	rendering_thread.join();
	gametimer_thread.join();
}

void App::exit()
{
	_window->close();
}
