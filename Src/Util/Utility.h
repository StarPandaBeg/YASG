#pragma once

#include "SFML/Graphics.hpp"

namespace util {
	class Utility
	{
	public:
		static sf::Vector2f toGlobalPosition(sf::Vector2i gridPosition);
		static sf::Vector2i getMid(sf::Vector2i size);

		template <typename T>
		static T constrain(T val, T min, T max);

		template <typename T>
		static sf::Vector2<T> vectorLerp(sf::Vector2<T> a, sf::Vector2<T> b, double val);

		static std::string toTimeString(sf::Time t);
		static std::string truncate(std::string str, size_t width, bool show_ellipsis = true);
	};

	template<typename T>
	inline T Utility::constrain(T val, T min, T max)
	{
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}

	template<typename T>
	inline sf::Vector2<T> Utility::vectorLerp(sf::Vector2<T> a, sf::Vector2<T> b, double val)
	{
		return sf::Vector2<T>(
			(T)std::lerp((double)a.x, (double)b.x, val),
			(T)std::lerp((double)a.y, (double)b.y, val)
			);
	}
}

