#include "GUI.h"

GUI* GUI::m_Instance = nullptr;

void GUI::Create()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GUI();
	}
}

void GUI::Destroy()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

GUI* GUI::GetInstance()
{
	return m_Instance;
}

void GUI::DrawGUI(aie::Renderer2D* renderer, aie::Font* font, aie::Input* input, int index)
{
	m_GUIType = index;
	//Update();
	Draw(renderer, font);
}

void GUI::GetHealth(int health)
{
	m_Health = health;
}

void GUI::GetScore(int score)
{
	m_Score = score;
}

void GUI::GetLives(int lives)
{
	m_lives = lives;
}

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::Update(aie::Input* input)
{
	// Checks for button click
	if (m_GUIType == 0)
	{
		int x = input->GetMouseX();
		int y = input->GetMouseY();

		for (int i = 0; i < m_ButtonList.Count(); i++)
		{
			

		}

	}
}

void GUI::Draw(aie::Renderer2D* renderer, aie::Font* font)
{

	switch (m_GUIType)
	{
	case 0:
		DrawMenu(renderer, font);
		break;

	case 1:
		DrawGame(renderer, font);
		break;

	case 2:
		DrawEndScreen(renderer, font);
	}
}

void GUI::DrawMenu(aie::Renderer2D* renderer, aie::Font* font)
{
	renderer->SetRenderColour(0, 0, 1, 1);
	renderer->DrawBox(100, 100, 50, 50, 0.0f, 0.0f);

	renderer->SetRenderColour(1, 0, 0, 1);
	renderer->DrawText2D(font, "Menu", 100, 100, 0.0f);
}

void GUI::DrawGame(aie::Renderer2D* renderer, aie::Font* font)
{

}

void GUI::DrawEndScreen(aie::Renderer2D* renderer, aie::Font* font)
{

}

void GUI::DrawButton(aie::Renderer2D* renderer, aie::Font* font)
{

}
