#include "SnakeRenderer.h"

#include "../Cells/SnakeCell.h"
#include "../Cells/SnakeHeadCell.h"

void snake::SnakeRenderer::onCellAdded(const events::Event& e)
{
	auto ev = static_cast<const events::snake::CellAddedEvent&>(e);
	auto cell = _snake->getLength() == 1 ? new cells::SnakeHeadCell(ev.position) : new cells::SnakeCell(ev.position);
	_grid->set(ev.position, cell);
}

void snake::SnakeRenderer::onCellRemoved(const events::Event& e)
{
	auto ev = static_cast<const events::snake::CellRemovedEvent&>(e);
	if (_snake->has(ev.position)) return;

	auto cell = _grid->remove(ev.position);
	delete cell;
	cell = nullptr;
}

void snake::SnakeRenderer::onCellMoved(const events::Event& e)
{
	auto ev = static_cast<const events::snake::CellMovedEvent&>(e);
	auto cell = _grid->get(ev.sourcePosition);
	cell->setGridPosition(ev.position);

	_grid->remove(ev.sourcePosition);
	delete _grid->remove(ev.position);
	_grid->set(ev.position, cell);
}

snake::SnakeRenderer::SnakeRenderer(Snake* snake, grid::Grid* grid) : _snake(snake), _grid(grid)
{
	_ids[0] = _snake->on<events::snake::CellAddedEvent>(std::bind(&snake::SnakeRenderer::onCellAdded, this, std::placeholders::_1));
	_ids[1] = _snake->on<events::snake::CellRemovedEvent>(std::bind(&snake::SnakeRenderer::onCellRemoved, this, std::placeholders::_1));
	_ids[2] = _snake->on<events::snake::CellMovedEvent>(std::bind(&snake::SnakeRenderer::onCellMoved, this, std::placeholders::_1));
	reset();
}

snake::SnakeRenderer::~SnakeRenderer()
{
	_snake->off<events::snake::CellAddedEvent>(_ids[0]);
	_snake->off<events::snake::CellRemovedEvent>(_ids[1]);
	_snake->off<events::snake::CellMovedEvent>(_ids[2]);
}

void snake::SnakeRenderer::reset()
{
	for (auto it = _snake->getCellPositions()->begin(); it != _snake->getCellPositions()->end(); it++) {
		onCellAdded(events::snake::CellAddedEvent(*it));
	}
}
