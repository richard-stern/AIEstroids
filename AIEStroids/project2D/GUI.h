// Author: Declan & Cameron

#pragma once
#include "Renderer2D.h"
#include "Font.h"
#include "Input.h"
#include "Application.h"
#include "Camera.h"

#define BORDER		-50.0f		// Text offset from top-left corner (px)
#define PADDING		32.0f		// Vertical offset between each line (px)
	
class GUI
{
public:
	static void Create();
	static void Destroy();
	static GUI* GetInstance();

	void Draw(aie::Renderer2D* renderer, aie::Font* font,  aie::Input* input);

	void SetHealth(int health);
	void SetScore(int score);
	void SetLives(int lives);

private:
	GUI();						// Constructor
	~GUI();						// Destructor

	static GUI* m_Instance;		// The GUI instance
	int m_Health;				// Displayed Health
	int m_Score;				// Displayed Score
	int m_Lives;				// Displayed Lives
};

