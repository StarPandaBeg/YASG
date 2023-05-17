#pragma once

#include <map>
#include "../Util/NewCamera.h"
#include "../Views/View.h"
#include "../Events/Event.h"
#include "../Events/EventDispatcher.h"

namespace events {
	namespace scene {
		struct SceneExitEvent : events::Event {
			int code;
			SceneExitEvent(int code = 0) : code(code) {}
		};
	}
}

namespace scenes {
	class Scene : public events::EventDispatcher
	{
	protected:
		util::NewCamera* _camera;
		std::multimap<int, views::ViewObj> _elements;

		int addView(views::View* v);
		views::View* removeView(int id);
		void exit(int code = 0);
	public:
		Scene(util::NewCamera* camera) : _camera(camera) {}
		~Scene();
		void render(sf::RenderWindow*);
	};
}

