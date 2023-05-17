#pragma once

#include <map>
#include <queue>

#include "Scenes/Scene.h"
#include "util/NewCamera.h"
#include "events/Event.h"
#include "Events/EventDispatcher.h"
#include "Views/View.h"

namespace sf {
	class RenderWindow;
}

namespace events {
	namespace window {
		struct WindowCloseEvent : events::Event {};
	}
}

class Window : public events::EventDispatcher
{
private:
	sf::RenderWindow* _renderWindow = nullptr;
	scenes::Scene* _scene = nullptr;
	util::NewCamera* _camera = nullptr;
	std::queue<scenes::Scene*> _readyToDestroyScenes;

	void render();
	void destroyScenes();
public:
	~Window();
	void setMainCamera(util::NewCamera*);
	void setRenderWindow(sf::RenderWindow*);
	void setScene(scenes::Scene*);
	scenes::Scene* getScene();
	void display();
	void run();
	void close();
};

