#pragma once

#include <queue>
#include <map>
#include <chrono>
#include "ITickable.h"

namespace util {
	class GameTimer
	{
	private:
		struct Worker {
			int id;
			util::ITickable* w;
		};

		std::queue<int> _toRemove;
		std::queue<Worker> _toAdd;

		std::map<int, util::ITickable*> _workers;
		std::chrono::steady_clock::time_point _lastUpdateTime;

		bool _active = false;
	public:
		static GameTimer* Default;
		void run();
		void stop();
		void tick();
		int add(util::ITickable*);
		void remove(int);
		double getDeltaTime();
	};
}