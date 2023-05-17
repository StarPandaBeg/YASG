#include "Utility.h"

#include "../GameConfig.h"

sf::Vector2f util::Utility::toGlobalPosition(sf::Vector2i gridPosition)
{
	return sf::Vector2f(
		gridPosition.x * CFG_CELL_WIDTH,
		gridPosition.y * CFG_CELL_HEIGHT
	);
}

sf::Vector2i util::Utility::getMid(sf::Vector2i size)
{
	return sf::Vector2i(
		size.x / 2,
		size.y / 2
	);
}

std::string util::Utility::toTimeString(sf::Time t)
{
	int ms = t.asMilliseconds();

	int h = ms / (1000 * 60 * 60);
	ms -= h * (1000 * 60 * 60);

	int m = ms / (1000 * 60);
	ms -= m * (1000 * 60);

	int s = ms / 1000;
	ms -= s * 1000;

	std::string timeString = (m <= 9 ? "0" : "") + std::to_string(m) + (s <= 9 ? ":0" : ":") + std::to_string(s);
	if (h > 0) timeString = std::to_string(h) + ":" + timeString;
	return timeString;
}

std::string util::Utility::truncate(std::string str, size_t width, bool show_ellipsis)
{
	if (str.length() > width)
		if (show_ellipsis)
			return str.substr(0, width) + "...";
		else
			return str.substr(0, width);
	return str;
}
