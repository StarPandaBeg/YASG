#include "TeleportCell.h"

#include "../Views/Renderers/TeleportCellRenderer.h"
#include "../Commands/SnakeTeleportationCommand.h"

void cells::TeleportCell::setDestination(sf::Vector2i destination)
{
	_destination = destination;
}

commands::IHitCommand* cells::TeleportCell::onCollisionWith(Cell* cell)
{
	auto entranceDirection = getGridPosition() - cell->getGridPosition();

	if (abs(entranceDirection.x) > 1) entranceDirection.x /= entranceDirection.x;
	if (abs(entranceDirection.y) > 1) entranceDirection.y /= entranceDirection.y;

	auto teleportTo = _destination + entranceDirection;
	return new commands::SnakeTeleportationCommand(teleportTo);
}

cells::TeleportCell::TeleportCell(sf::Vector2i pos, sf::Vector2i destination) : Cell(pos), _destination(destination)
{
	_renderer = new views::renderers::TeleportCellRenderer(getPosition(), sf::Color::White);
}

cells::TeleportCell::~TeleportCell()
{
	delete _renderer;
}

views::renderers::ICustomRenderer* cells::TeleportCell::getCustomRenderer()
{
	return _renderer;
}

void cells::TeleportCell::setColor(sf::Color c)
{
	_portalColor = c;
	_renderer->setColor(c);
}
