#pragma once

#include "../Views/View.h"
#include "../Commands/IHitCommand.h"

namespace views {
	class View;
}

namespace commands {
	class IHitCommand;
}

namespace cells {
	class Cell : public views::View {
	protected:
		sf::Vector2i _gridPosition;
	public:
		Cell(sf::Vector2i position);

		sf::Vector2i getGridPosition() { return _gridPosition; }
		virtual void setGridPosition(sf::Vector2i pos);
		virtual commands::IHitCommand* onCollisionWith(Cell* cell) { return nullptr; }
	};
}