#pragma once

#include "SFML/System/Clock.hpp"

namespace util {
	class Clock
	{
	private:
		sf::Clock _clockMain;
		sf::Clock _clockStop;
		sf::Time _diffTime = sf::Time::Zero;

		bool _wasStarted = false;
		bool _started = false;
	public:
		Clock(bool autoStart = true);
		sf::Time getElapsedTime();
		void restart();
		void start();
		void stop();
		void setState(bool state);
	};
}
