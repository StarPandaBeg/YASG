#include "ResourceManager.h"

util::ResourceManager* util::ResourceManager::instance()
{
	static ResourceManager instance;
	return &instance;
}

void util::ResourceManager::load()
{
	loadTextures();
	loadFonts();
}

sf::Texture* util::ResourceManager::getTexture(const char* id)
{
	return getAsset(_textureAssets, id);
}

sf::Font* util::ResourceManager::getFont(const char* id)
{
	return getAsset(_fontAssets, id);
}

void util::ResourceManager::loadTextures()
{
	for (auto it = _textureMap.begin(); it != _textureMap.end(); it++) {
		auto id = it->first;
		auto path = it->second;

		if (!loadAsset(_textureAssets, id, path)) continue;
		if (std::find(_texturesToRepeat.begin(), _texturesToRepeat.end(), id) != _texturesToRepeat.end()) {
			_textureAssets.getAsset(id)->setRepeated(true);
		}
	}
}

void util::ResourceManager::loadFonts()
{
	for (auto it = _fontMap.begin(); it != _fontMap.end(); it++) {
		auto id = it->first;
		auto path = it->second;

		if (!loadAsset(_fontAssets, id, path)) continue;
	}
}
