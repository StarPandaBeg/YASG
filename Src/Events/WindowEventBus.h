#pragma once

#include <queue>
#include <map>
#include "IWindowEventTickable.h"

namespace util {

	class WindowEventBus {
	private:
		struct Worker {
			int id;
			util::IWindowEventTickable* w;
		};

		std::queue<int> _toRemove;
		std::queue<Worker> _toAdd;
		std::map<int, util::IWindowEventTickable*> _workers;
		WindowEventBus() {};
	public:
		static WindowEventBus* instance();
		void tick(sf::Event e);
		int add(util::IWindowEventTickable*);
		void remove(int);
	};
}