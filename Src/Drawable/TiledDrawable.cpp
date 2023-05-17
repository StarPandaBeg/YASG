#include "TiledDrawable.h"

void drawable::TiledDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = _texture;
	target.draw(_vertices, states);
}

void drawable::TiledDrawable::createQuad(sf::Vertex* quad, sf::Vector2i tileSize, sf::Vector2i pos)
{
	auto tu = abs(pos.x) % 4;
	auto tv = abs(pos.y) % 4;

	quad[0].position = sf::Vector2f(pos.x * tileSize.x * 1.0f, pos.y * tileSize.y * 1.0f);
	quad[1].position = sf::Vector2f((pos.x + 1) * tileSize.x * 1.0f, pos.y * tileSize.y * 1.0f);
	quad[2].position = sf::Vector2f((pos.x + 1) * tileSize.x * 1.0f, (pos.y + 1) * tileSize.y * 1.0f);
	quad[3].position = sf::Vector2f(pos.x * tileSize.x * 1.0f, (pos.y + 1) * tileSize.y * 1.0f);

	quad[0].texCoords = sf::Vector2f(tu * tileSize.x * 1.0f, tv * tileSize.y * 1.0f);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x * 1.0f, tv * tileSize.y * 1.0f);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x * 1.0f, (tv + 1) * tileSize.y * 1.0f);
	quad[3].texCoords = sf::Vector2f(tu * tileSize.x * 1.0f, (tv + 1) * tileSize.y * 1.0f);
}
