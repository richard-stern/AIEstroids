#include "TextureManager.h"

//Singleton
TextureManager* TextureManager::m_Instance = nullptr;

TextureManager::TextureManager()
{
	m_Textures = new std::unordered_map<const char*, aie::Texture*>();
}

TextureManager::~TextureManager()
{
	//Unload all textures
	for (auto iter = m_Textures->begin(); iter != m_Textures->end(); iter++)
	{
		iter->second->Unload();

		delete iter->second;
		//Maybe needed
		//delete iter->first;
	}
	delete m_Textures;

}

//Gets an instance, creates it if it doesn't already exist
TextureManager* TextureManager::Get()
{
	if (!m_Instance)
	{
		TextureManager::m_Instance = new TextureManager();
	}

	return m_Instance;
}

void TextureManager::Destroy()
{
	if (TextureManager::m_Instance)
		delete TextureManager::m_Instance;
}


aie::Texture* TextureManager::LoadTexture(const char* filePath)
{
	//Check if texture already exists
	auto found = m_Textures->find(filePath);

	if (found == m_Textures->end())
	{
		//Texture Not Found, Load it in
		aie::Texture* texture = new aie::Texture(filePath);
		m_Textures->emplace(filePath, texture);
		return texture;
	}
	else
		return found->second;
}

aie::Font* TextureManager::LoadFont(const char* filePath, int size)
{
	//Check if texture already exists
	auto found = m_Font->find(filePath);

	if (found == m_Font->end())
	{
		//Texture Not Found, Load it in
		aie::Font* font = new aie::Font(filePath,size);
		m_Font->emplace(filePath, font);
		return font;
	}
	else
		return found->second;
}
