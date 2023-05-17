#pragma once

#include "IHitCommand.h"

namespace commands {
	class SnakeDieCommand : public IHitCommand
	{
	public:
		SnakeDieCommand() {};
		bool execute(snake::Snake* snake) override;
	};
}