#include "Scene.h"

int scenes::Scene::addView(views::View* v)
{
	auto id = rand() % 100000;
	auto layer = v->getOrderInLayer();
	auto viewObj = views::ViewObj{ id, v };
	_elements.emplace(layer, viewObj);
	return id;
}

views::View* scenes::Scene::removeView(int id)
{
	for (auto it = _elements.begin(); it != _elements.end(); it++) {
		if (it->second.id == id) {
			_elements.erase(it);
			return it->second.v;
		}
	}
	return nullptr;
}

void scenes::Scene::exit(int code)
{
	emit(events::scene::SceneExitEvent(code));
}

scenes::Scene::~Scene()
{
	for (auto elementPair : _elements) {
		delete elementPair.second.v;
	}
}

void scenes::Scene::render(sf::RenderWindow* window)
{
	for (const auto& elementPair : _elements) {
		elementPair.second.v->render(window);
	}
}
