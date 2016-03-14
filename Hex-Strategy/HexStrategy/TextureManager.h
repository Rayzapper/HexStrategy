#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML\Graphics.hpp>

class TextureManager
{
public:
	static TextureManager& GetInstance();
	sf::Texture* GetTexture(int textureID);
private:
	TextureManager();
	TextureManager(const TextureManager &textureManager);
	TextureManager& operator=(const TextureManager &textureManager);
	~TextureManager();
	void InternalClear();
	sf::Texture mMercenaryTexture;
};

#endif