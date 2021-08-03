//Written by Jayden Hunter
//		-- Get Outta 'Ere
#include "TextureManager.h"

//Singleton
TextureManager* TextureManager::m_Instance = nullptr;

TextureManager::TextureManager()
{
	m_Textures = new std::unordered_map<const char*, aie::Texture*>();
	m_Font = new std::unordered_map<const char*, aie::Font*>();
}

TextureManager::~TextureManager()
{
	//Unload all textures
	for (auto iter = m_Textures->begin(); iter != m_Textures->end(); iter++)
	{
		iter->second->Unload();

		delete iter->second;
	}
	delete m_Textures;

	//Unload all fonts
	for (auto iter = m_Font->begin(); iter != m_Font->end(); iter++)
	{
		delete iter->second;
	}
	delete m_Font;

}

void TextureManager::Create()
{
	if (!m_Instance)
	{
		TextureManager::m_Instance = new TextureManager();
	}
}

//Gets an instance, creates it if it doesn't already exist
TextureManager* TextureManager::Get()
{
	if (!m_Instance)
		return nullptr;

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
	//Check if font already exists
	auto found = m_Font->find(filePath);

	if (found == m_Font->end())
	{
		//Font Not Found, Load it in
		aie::Font* font = new aie::Font(filePath,size);
		m_Font->emplace(filePath, font);
		return font;
	}
	else
		return found->second;
}
