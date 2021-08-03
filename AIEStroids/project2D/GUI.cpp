#include "GUI.h"
// Sets the instance to nullptr
GUI* GUI::m_Instance = nullptr;

// Creates the GUI if there isn't an existing instance
void GUI::Create()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GUI();
	}
}

// Destroys the GUI if there is an existing instance
void GUI::Destroy()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

// Retruns the instance
GUI* GUI::GetInstance()
{
	Create(); // make sure we have an instance
	return m_Instance;
}

// Draws the Game UI
void GUI::Draw(aie::Renderer2D* renderer, aie::Font* font, aie::Input* input)
{
	// Needs too be updated to look neater
	int y = aie::Application::GetInstance()->GetWindowHeight() - 20;
	int x = 20;

	renderer->SetRenderColour(1.0f, 0.0f, 0.0f, 1.0f);
	renderer->DrawText2D(font, "Health" + m_Health, x, y, 0.0f);
	renderer->DrawText2D(font, "Score" + m_Score, x, (y - 30), 0.0f);
	renderer->DrawText2D(font, "Lives" + m_lives, x, (y - 60), 0.0f);
}

// The player's health input
void GUI::SetHealth(int health)
{
	m_Health = health;
}

// The player's score input
void GUI::SetScore(int score)
{
	m_Score = score;
}

// The player's lives input
void GUI::SetLives(int lives)
{
	m_lives = lives;
}

// Constructor
GUI::GUI()
{
}

// Destructor
GUI::~GUI()
{
}
