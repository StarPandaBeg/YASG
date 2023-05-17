#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include "App.h"

#include "Util/HighScoreManager.h"
#include <fstream>

sf::RenderWindow* create_window() {
	auto window = new sf::RenderWindow(
		sf::VideoMode(
			CFG_WINDOW_WIDTH,
			CFG_WINDOW_HEIGHT),
		CFG_WINDOW_TITLE,
		sf::Style::Titlebar | sf::Style::Close);
	window->setVerticalSyncEnabled(true);
	// window->setFramerateLimit(60);
	window->setActive(false);

	sf::Image icon;
	icon.loadFromFile("Assets/Textures/icon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	return window;
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	auto window = create_window();
	auto app = new App(window);

	app->run();
	return 0;
}