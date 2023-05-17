#pragma once

#include "SFML/Graphics.hpp"
#include "Window.h"

#include "SnakeGame.h"
#include "Views/RectangleView.h"
#include "Util/NewCamera.h"

class App
{
private:
	enum State {
		MAIN_MENU,
		GAME,
		RATING,
		CONFIG
	};

	sf::RenderWindow* _renderWindow;
	Window* _window;
	util::NewCamera* _camera;
	int _eventIds[2];

	int _state = MAIN_MENU;
	scenes::Scene* _scene;
	SnakeGame* _game;

	util::NewCamera* createCamera();
	void onWindowClose(const events::Event& e);
	void onSceneExit(const events::Event& e);

	void loadScene(scenes::Scene* s);
public:
	App(sf::RenderWindow* window);
	~App();
	void run();
	void exit();
};

