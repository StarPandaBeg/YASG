#pragma once

#include "Cell.h"
#include "../Commands/IHitCommand.h"

namespace cells {
	class SnakeCell : public Cell
	{
	public:
		SnakeCell(sf::Vector2i position) : Cell(position) {}
		commands::IHitCommand* onCollisionWith(Cell* cell) override;
		const char* getTextureId() override;

		int getOrderInLayer() override;
	};
}