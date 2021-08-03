#pragma once
#include <unordered_map>
#include "Texture.h"
#include "Font.h"

class TextureManager
{
public:
	static void Create();
	static TextureManager* Get();
	static void Destroy();

	//Loads a texture if it exists, if not, it creates it
	aie::Texture* LoadTexture(const char* filePath);
	aie::Font* LoadFont(const char* filePath, int size = 24);

private:
	TextureManager();
	~TextureManager();

	std::unordered_map<const char*, aie::Texture*>* m_Textures;
	std::unordered_map<const char*, aie::Font*>* m_Font;
	static TextureManager* m_Instance;
};

