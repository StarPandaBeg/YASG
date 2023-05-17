#pragma once

#include "IHitCommand.h"
#include "../Snake/Snake.h"

namespace commands {
	class SnakeDecreaseCommand : public IHitCommand
	{
	public:
		bool execute(snake::Snake* snake) override;
	};
}