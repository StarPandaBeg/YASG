#pragma once

#include "IHitCommand.h"

namespace commands {
	class SnakeTeleportationCommand : public IHitCommand
	{
	private:
		sf::Vector2i _to;
	public:
		SnakeTeleportationCommand(sf::Vector2i teleportTo) : _to(teleportTo) {}
		bool execute(snake::Snake* snake) override;
	};
}

