#pragma once

#include "IHitCommand.h"
#include "../Snake/Snake.h"
#include "../Cells/Cell.h"

namespace commands {
	class SnakeTailCutCommand : public IHitCommand
	{
	private:
		cells::Cell* _cell;
	public:
		SnakeTailCutCommand(cells::Cell* cell) : _cell(cell) {};
		bool execute(snake::Snake* snake) override;
	};
}