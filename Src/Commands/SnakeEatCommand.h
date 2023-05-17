#pragma once

#include "IHitCommand.h"
#include "../Snake/Snake.h"
#include "../Cells/Cell.h"
#include "../Cells/Food/AppleCell.h"

namespace game {
	namespace cell {
		class AppleCell;
	}
}

namespace commands {
	class SnakeEatCommand : public IHitCommand
	{
	private:
		cells::food::AppleCell* _apple;
	public:
		SnakeEatCommand(cells::Cell* cell) : _apple((cells::food::AppleCell*)cell) {};
		bool execute(snake::Snake* snake) override;
	};
}