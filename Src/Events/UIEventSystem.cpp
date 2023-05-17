#include "UIEventSystem.h"

#include "WindowEventBus.h"
#include <iostream>

void util::UIEventSystem::process(Data* data, sf::Event e)
{
	if (data->interactable == nullptr) return;
	if (!data->interactable->isInteractable()) {
		for (int i = 0; i < 5; i++)
			data->mouseDown[i] = false;
		data->inArea = false;
		return;
	}
	auto area = data->interactable->getClickableArea();
	sf::Vector2f pos;
	switch (e.type)
	{
		case sf::Event::MouseButtonPressed:
			pos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
			if (!area.contains(pos)) return;
			data->interactable->setClickState(true);
			data->mouseDown[e.mouseButton.button] = true;
			break;
		case sf::Event::MouseButtonReleased:
			pos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
			data->interactable->setClickState(false, area.contains(pos));
			data->mouseDown[e.mouseButton.button] = false;
			break;

		case sf::Event::MouseMoved:
			pos = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
			if (area.contains(pos)) {
				if (!data->inArea) {
					data->inArea = true;
					data->interactable->setHoverState(true);
				}
			}
			else {
				if (data->inArea) {
					data->inArea = false;
					data->interactable->setHoverState(false);
				}
			}
			break;

		case sf::Event::TextEntered :
			auto code = e.text.unicode;
			if (code > 128) break;
			auto c = static_cast<char>(code);
			data->interactable->onKeyEnter(c);
			break;
	}
}

util::UIEventSystem::UIEventSystem() {
	WindowEventBus::instance()->add(this);
}

util::UIEventSystem* util::UIEventSystem::instance()
{
	static UIEventSystem instance;
	return &instance;
}

void util::UIEventSystem::tick(sf::Event e)
{
	for (auto interactable : _map) {
		process(interactable.second, e);
		if (_skipTick) {
			_skipTick = false;
			break;
		}
	}
}

util::UIEventSystem::~UIEventSystem()
{
	for (auto interactable : _map) {
		delete interactable.second;
	}
}

int util::UIEventSystem::add(views::ui::IInteractable* interactable)
{
	auto id = rand() % 100000;
	auto data = new Data;
	data->interactable = interactable;
	_map[id] = data;
	return id;
}

void util::UIEventSystem::remove(int id)
{
	auto found = _map.find(id);
	if (found != _map.end()) _map.erase(found);
	_skipTick = true;
}
