#pragma once

#include "../Snake/Snake.h"

namespace snake {
	class Snake;
}

namespace commands {
	class IHitCommand
	{
	public:
		virtual bool execute(snake::Snake* snake) { return false; };
	};
}