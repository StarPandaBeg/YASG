#include "GameTimer.h"

#include <thread>
#include <chrono>

#include "InputSystem.h"

util::GameTimer* util::GameTimer::Default = new util::GameTimer();

std::chrono::steady_clock::time_point getTimeNow() {
	return std::chrono::high_resolution_clock::now();
}

void util::GameTimer::run()
{
	_lastUpdateTime = getTimeNow();
	_active = true;

	while (_active) {
		tick();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void util::GameTimer::stop()
{
	_active = false;
}

void util::GameTimer::tick()
{
	for (auto it = _workers.begin(); it != _workers.end(); it++) {
		it->second->tick();
	}
	_lastUpdateTime = getTimeNow();

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

int util::GameTimer::add(util::ITickable* w)
{
	Worker worker;
	worker.id = rand() % 10000000;
	worker.w = w;
	_toAdd.push(worker);
	return worker.id;
}

void util::GameTimer::remove(int id)
{
	auto found = _workers.find(id);
	if (found != _workers.end()) _toRemove.push(id);
}

double util::GameTimer::getDeltaTime()
{
	return (getTimeNow() - _lastUpdateTime).count();
}
