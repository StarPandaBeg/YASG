#pragma once

#include "SnakeCell.h"
#include "../Util/ResourceManager.h"

namespace cells {
	class SnakeHeadCell : public SnakeCell
	{
	public:
		SnakeHeadCell(sf::Vector2i position) : SnakeCell(position) {}
		const char* getTextureId() override { return TEXTURE_SNAKE_HEAD; }
		int getOrderInLayer() override { return LAYER_SNAKE_HEAD; }
	};
}