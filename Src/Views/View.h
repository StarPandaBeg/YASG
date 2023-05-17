#pragma once

#include "SFML/Graphics.hpp"
#include "Renderers/ICustomRenderer.h"
#include "../Util/Layers.h"

namespace sf {
	class RenderWindow;
}

namespace views {
	enum Alignment {
		LEFT = 0b00,
		CENTER_X = 0b01,
		RIGHT = 0b10,

		TOP = 0b00 << 2,
		CENTER_Y = 0b01 << 2,
		BOTTOM = 0b10 << 2
	};

	class View
	{
	protected:
		sf::RectangleShape* _bounds;
		sf::Sprite* _defaultSprite = new sf::Sprite();
		char* _oldTextureId = nullptr;
		const char* _textureId = nullptr;
		bool _enabled = true;
		uint8_t _lastAlignment = 0;

		virtual const char* getTextureId() { return _textureId; }
		virtual renderers::ICustomRenderer* getCustomRenderer() { return nullptr; };

		void recreateSpriteTexture(const char* id);
		static void align(sf::Transformable* obj, sf::FloatRect bounds, uint8_t alignment);
		virtual void _align(uint8_t alignment);
	public:
		View(sf::Vector2f position) : View(position, sf::Vector2f()) {}
		View(sf::Vector2f position, sf::Vector2f size);
		virtual ~View();

		virtual void render(sf::RenderWindow* window);
		virtual void setPosition(sf::Vector2f);
		virtual sf::Vector2f getPosition();
		void align(uint8_t alignment);
		sf::RectangleShape* getBounds();
		void setTextureId(const char* id);
		void setColor(sf::Color c);

		virtual int getOrderInLayer();
		bool isEnabled();
		virtual void setEnabled(bool enabled);
	};

	struct ViewObj {
		int id;
		View* v;
	};
}

