#pragma once

#include "SFML/Graphics.hpp"
#include "../Cells/Cell.h"
#include "../Events/Event.h"
#include "../Events/EventDispatcher.h"
#include "Shapes/IGridShape.h"

#include <vector>
#include <unordered_map>
#include <mutex>

namespace events {
	namespace grid {
		struct ShapeChangedEvent : events::Event {};
	}
}

namespace util {
	template<class T>
	class VectorHash;

	template<>
	class VectorHash<sf::Vector2i>
	{
	public:
		std::size_t operator()(sf::Vector2i const& s) const {
			std::size_t h1 = std::hash<int>()(s.x);
			std::size_t h2 = std::hash<int>()(s.y);
			return h1 ^ (h2 << 1);
		}
	};
}

namespace grid {
	typedef std::unordered_map<sf::Vector2i, cells::Cell*, util::VectorHash<sf::Vector2i>> CellMap;

	class Grid : public events::EventDispatcher
	{
	private:
		CellMap _cells;
		sf::Vector2i _size;

		shapes::IGridShape* _shape = nullptr;
	public:
		std::mutex lock;

		Grid(sf::Vector2i);
		Grid(int width, int height) : Grid(sf::Vector2i(width, height)) {};
		~Grid();

		void clear();
		void set(sf::Vector2i pos, cells::Cell* cell);
		cells::Cell* remove(sf::Vector2i);
		cells::Cell* get(sf::Vector2i);
		CellMap* getCells();
		sf::Vector2i getSize();
		sf::Vector2i getOppositePosition(sf::Vector2i pos, sf::Vector2i dir);

		shapes::IGridShape* getShape();
		void setShape(shapes::IGridShape* shape);
		bool contains(sf::Vector2i pos);
	};
}
