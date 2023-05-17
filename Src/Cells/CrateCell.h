#pragma once

#include "Cell.h"

namespace cells {
	class CrateCell : public Cell
	{
	private:
		bool _destructable;
	public:
		CrateCell(sf::Vector2i position, bool destructable = true);
		commands::IHitCommand* onCollisionWith(Cell* cell) override;
		const char* getTextureId() override;
	};
}