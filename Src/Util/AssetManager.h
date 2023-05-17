#pragma once

#include <unordered_map>

namespace util {
	template <class T>
	class AssetManager {
	public:
		~AssetManager();
		void addAsset(const char* id, T* asset);
		T* getAsset(const char* id) const;
	private:
		std::unordered_map<const char*, T*> _assetMap;
	};

	template<class T>
	inline AssetManager<T>::~AssetManager()
	{
		for (auto it = _assetMap.begin(); it != _assetMap.end(); it++) {
			delete it->second;
		}
	}

	template<class T>
	inline void AssetManager<T>::addAsset(const char* id, T* asset)
	{
		if (_assetMap.count(id))
			delete _assetMap[id];
		_assetMap[id] = asset;
	}

	template<class T>
	inline T* AssetManager<T>::getAsset(const char* id) const
	{
		return _assetMap.at(id);
	}
}

