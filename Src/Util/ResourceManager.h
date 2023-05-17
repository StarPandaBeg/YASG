#pragma once

#include "AssetManager.h"
#include "SFML/Graphics.hpp"

#define TEXTURE_EMPTY "empty"
#define TEXTURE_DESK "desk"
#define TEXTURE_SNAKE_HEAD "snakeHead"
#define TEXTURE_SNAKE_BLOCK "snakeBlock"
#define TEXTURE_APPLE "foodApple"
#define TEXTURE_CHERRY "foodCherry"
#define TEXTURE_BANANA "foodBanana"
#define TEXTURE_GRASS "grass"
#define TEXTURE_CRATE_WOOD "crateWood"
#define TEXTURE_CRATE_METAL "crateMetal"
#define TEXTURE_PORTAL_BASE "portalBase"
#define TEXTURE_PORTAL_GLOW "portalGlow"
#define TEXTURE_UI_CLOCK "uiClock"
#define TEXTURE_UI_BUTTON_LEFT "uiButtonLeft"
#define TEXTURE_UI_BUTTON_RIGHT "uiButtonRight"
#define TEXTURE_UI_MENU_BACKGROUND "uiMenuBackground"
#define TEXTURE_UI_LOGO "uiLogo"
#define FONT_PRICEDOWN "pricedown"

namespace util {
	class ResourceManager
	{
	public:
		static ResourceManager* instance();
		void load();
		sf::Texture* getTexture(const char* id);
		sf::Font* getFont(const char* id);
	private:
		ResourceManager() {}
		void loadTextures();
		void loadFonts();

		template <class T>
		bool loadAsset(AssetManager<T>& manager, const char* id, const char* path);

		template <class T>
		T* getAsset(AssetManager<T>& manager, const char* id);

		AssetManager<sf::Texture> _textureAssets;
		AssetManager<sf::Font> _fontAssets;

		inline static std::map<const char*, const char*> _textureMap = {
			{TEXTURE_EMPTY, "Assets/Textures/empty.png"},
			{TEXTURE_DESK, "Assets/Textures/tiles.png"},
			{TEXTURE_SNAKE_HEAD, "Assets/Textures/snake_head.png"},
			{TEXTURE_SNAKE_BLOCK, "Assets/Textures/snake_block.png"},
			{TEXTURE_APPLE, "Assets/Textures/food_apple.png"},
			{TEXTURE_CHERRY, "Assets/Textures/food_cherry.png"},
			{TEXTURE_BANANA, "Assets/Textures/food_banana.png"},
			{TEXTURE_GRASS, "Assets/Textures/grass.png"},
			{TEXTURE_CRATE_WOOD, "Assets/Textures/crate_wood.png"},
			{TEXTURE_CRATE_METAL, "Assets/Textures/crate_metal.png"},
			{TEXTURE_PORTAL_BASE, "Assets/Textures/portal_base.png"},
			{TEXTURE_PORTAL_GLOW, "Assets/Textures/portal_glow.png"},
			{TEXTURE_UI_CLOCK, "Assets/Textures/clock.png"},
			{TEXTURE_UI_BUTTON_LEFT, "Assets/Textures/btn_left.png"},
			{TEXTURE_UI_BUTTON_RIGHT, "Assets/Textures/btn_right.png"},
			{TEXTURE_UI_MENU_BACKGROUND, "Assets/Textures/menu.png"},
			{TEXTURE_UI_LOGO, "Assets/Textures/logo.png"},
		};
		inline static std::vector<const char*> _texturesToRepeat = {
			TEXTURE_GRASS,
			TEXTURE_EMPTY
		};
		inline static std::map<const char*, const char*> _fontMap = {
			{FONT_PRICEDOWN, "Assets/Fonts/pricedown.ttf"}
		};
	};

	template<class T>
	inline bool ResourceManager::loadAsset(AssetManager<T>& manager, const char* id, const char* path)
	{
		auto asset = new T;
		auto loaded = asset->loadFromFile(path);

		if (!loaded) {
			delete asset;
			return false;
		}
		manager.addAsset(id, asset);
		return true;
	}
	template<class T>
	inline T* ResourceManager::getAsset(AssetManager<T>& manager, const char* id)
	{
		return manager.getAsset(id);
	}
}

