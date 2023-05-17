#include "Clock.h"

util::Clock::Clock(bool autoStart)
{
    if (autoStart) start();
}

sf::Time util::Clock::getElapsedTime()
{
    if (_started)
        return _clockMain.getElapsedTime() - _diffTime;
    return sf::Time::Zero;
}

void util::Clock::restart()
{
    _diffTime = sf::Time::Zero;
    _clockMain.restart();
    _clockStop.restart();
}

void util::Clock::start()
{
    if (_started) return;
    if (_wasStarted)
        _diffTime += _clockStop.getElapsedTime();
    _wasStarted = true;
    _started = true;
}

void util::Clock::stop()
{
    if (!_started) return;
    _clockStop.restart();
    _started = false;
}

void util::Clock::setState(bool state)
{
    if (state) start();
    else stop();
}
