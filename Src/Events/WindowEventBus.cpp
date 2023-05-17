#include "WindowEventBus.h"

util::WindowEventBus* util::WindowEventBus::instance()
{
	static WindowEventBus instance;
	return &instance;
}

void util::WindowEventBus::tick(sf::Event e)
{
	for (auto it = _workers.begin(); it != _workers.end(); it++) {
		it->second->tick(e);
	}
	while (!_toRemove.empty()) {
		_workers.erase(_toRemove.front());
		_toRemove.pop();
	}
	while (!_toAdd.empty()) {
		auto w = _toAdd.front();
		_toAdd.pop();
		_workers[w.id] = w.w;
	}
}

int util::WindowEventBus::add(util::IWindowEventTickable* w)
{
	Worker worker;
	worker.id = rand() % 10000000;
	worker.w = w;
	_toAdd.push(worker);
	return worker.id;
}

void util::WindowEventBus::remove(int id)
{
	auto found = _workers.find(id);
	if (found != _workers.end()) _toRemove.push(id);
}
