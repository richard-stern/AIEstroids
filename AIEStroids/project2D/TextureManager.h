#pragma once
#include <unordered_map>
#include "Texture.h"

class TextureManager
{
public:
	static TextureManager* Get();
	static void Destroy();

	//Loads a texture if it exists, if not, it creates it
	aie::Texture* LoadTexture(const char* filePath);

private:
	TextureManager();
	~TextureManager();

	std::unordered_map<const char*, aie::Texture*>* m_Textures;
	static TextureManager* m_Instance;
};

