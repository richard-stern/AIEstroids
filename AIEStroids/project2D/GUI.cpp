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

void GUI::Draw(aie::Renderer2D* renderer, int index)
{
	switch (index)
	{
	case 0: 
		DrawMenu(renderer);
		break;

	case 1:
		DrawGame(renderer);
		break;

	case 2:
		DrawEndScreen(renderer);
	}
}

void GUI::SetHealth()
{
}

void GUI::AddScore()
{
}

void GUI::GetScore()
{
}

void GUI::SetLives()
{
}

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::DrawMenu(aie::Renderer2D* renderer)
{
	
}

void GUI::DrawGame(aie::Renderer2D* renderer)
{
}

void GUI::DrawEndScreen(aie::Renderer2D* renderer)
{
}

void GUI::DrawButton(aie::Renderer2D* renderer)
{
}
