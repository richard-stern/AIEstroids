#pragma once
#include "Renderer2D.h"

class GUI
{
public:

	static void Create();
	static void Destroy();

	GUI* GetInstance();

	void Draw(aie::Renderer2D* renderer, int index);

	void SetHealth();

	void SetHealth();

	void AddScore();

	void GetScore();

	void SetLives();


private:

	GUI();
	~GUI();
	
	void DrawMenu(aie::Renderer2D* renderer);
	void DrawGame(aie::Renderer2D* renderer);
	void DrawEndScreen(aie::Renderer2D* renderer);

	void DrawButton(aie::Renderer2D* renderer);
	static GUI* m_Instance;
	aie::Renderer2D* renderer;

};

