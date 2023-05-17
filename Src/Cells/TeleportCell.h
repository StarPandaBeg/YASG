#pragma once

#include "Cell.h"
#include "../Views/Renderers/TeleportCellRenderer.h"

namespace cells {
	class TeleportCell : public Cell
	{
	private:
		sf::Color _portalColor;
		sf::Vector2i _destination;
		views::renderers::TeleportCellRenderer* _renderer;
	public:
		TeleportCell(sf::Vector2i pos, sf::Vector2i destination);
		TeleportCell(sf::Vector2i pos) : TeleportCell(pos, sf::Vector2i()) {}
		~TeleportCell();
		commands::IHitCommand* onCollisionWith(Cell* cell) override;
		views::renderers::ICustomRenderer* getCustomRenderer() override;
		void setDestination(sf::Vector2i destination);
		void setColor(sf::Color c);
	};
}

