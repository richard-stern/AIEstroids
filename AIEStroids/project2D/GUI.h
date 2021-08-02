#pragma once
#include "Renderer2D.h"
#include "Font.h"
#include "Input.h"
#include "DynamicArray.h"
#include "Vector2.h"

class Button
{
	Vector2 position;
};

class GUI
{
public:

	
	static void Create();
	static void Destroy();

	GUI* GetInstance();

	void DrawGUI(aie::Renderer2D* renderer, aie::Font* font,  aie::Input* input, int index);


private:

	GUI();
	~GUI();
	
	void Update(aie::Input* input);
	void Draw(aie::Renderer2D* renderer, aie::Font* font );

	void GetHealth(int health);

	void GetScore(int score);

	void GetLives(int lives);

	void DrawMenu(aie::Renderer2D* renderer, aie::Font* font);
	void DrawGame(aie::Renderer2D* renderer, aie::Font* font);
	void DrawEndScreen(aie::Renderer2D* renderer, aie::Font* font);

	void DrawButton(aie::Renderer2D* renderer, aie::Font* font);
	static GUI* m_Instance;
	DynamicArray<Button*> m_ButtonList;

	int m_GUIType;
	int m_Health;
	int m_Score;
	int m_lives;
};

