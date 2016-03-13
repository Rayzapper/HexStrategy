#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class TextureManager
{
public:
	static TextureManager& GetInstance();
private:
	TextureManager();
	TextureManager(const TextureManager &textureManager);
	TextureManager& operator=(const TextureManager &textureManager);
	~TextureManager();
	void InternalClear();
};

#endif