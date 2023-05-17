#include "Window.h"

#include <SFML/Graphics.hpp>

#include "Util/GameTimer.h"
#include "Util/InputSystem.h"
#include "Events/WindowEventBus.h"
#include "Events/Event.h"

using namespace events::input;

void Window::render()
{
	if (_scene == nullptr) return;
	_scene->render(_renderWindow);
}

void Window::destroyScenes()
{
	while (!_readyToDestroyScenes.empty()) {
		auto scene = _readyToDestroyScenes.front();
		_readyToDestroyScenes.pop();
		delete scene;
		scene = nullptr;
	}
}

Window::~Window()
{
	destroyScenes();
	delete _camera;
}

void Window::setMainCamera(util::NewCamera* camera)
{
	delete _camera;
	_camera = camera;
}

void Window::setRenderWindow(sf::RenderWindow* window)
{
	_renderWindow = window;
}

void Window::setScene(scenes::Scene* scene)
{
	if (_scene != nullptr) _readyToDestroyScenes.push(_scene);
	_scene = scene;
}

scenes::Scene* Window::getScene()
{
	return _scene;
}

void Window::display()
{
	if (_renderWindow != nullptr)
	{
		_renderWindow->setActive(true);
		while (_renderWindow->isOpen())
		{
			_renderWindow->clear(sf::Color::Black);
			render();
			_renderWindow->display();

			_camera->deployTo(_renderWindow);
			destroyScenes();
		}
		_renderWindow->setActive(false);
	}
}

void Window::run()
{
	_renderWindow->setActive(false);
	while (_renderWindow->isOpen())
	{
		sf::Event event;
		while (_renderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				close();
				break;
			}
			util::InputSystem::instance()->update(event);
			util::WindowEventBus::instance()->tick(event);
		}
	}
}

void Window::close()
{
	emit(events::window::WindowCloseEvent());
	_renderWindow->close();
}
