// Author: Declan & Cameron

#include "GUI.h"

// Singleton initialisation
GUI* GUI::m_Instance = nullptr;

#pragma region Singleton Functions
// Singleton creation
void GUI::Create()
{
	if (m_Instance == nullptr)
		m_Instance = new GUI();
}

// Singleton deletion
void GUI::Destroy()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

// Gets the GUI instance
GUI* GUI::GetInstance()
{
	Create();
	return m_Instance;
}

// Constructor - Sets initial score values
GUI::GUI()
{
	m_Health = 100;
	m_Score = 0;
	m_Lives = 5;
}

// Destructor - Does nothing
GUI::~GUI()
{
}
#pragma endregion

// Draw loop - Draws GUI
void GUI::Draw(aie::Renderer2D* renderer, aie::Font* font, aie::Input* input)
{
	// Calculate top-left position using camera position, window height and font height
	Vector2 cameraPos = Camera::GetInstance()->GetPosition();
	float windowH = (float)aie::Application::GetInstance()->GetWindowHeight();
	float xOrigin = cameraPos.x;
	float yOrigin = cameraPos.y + windowH - font->GetStringHeight("A");

	// Get scores as strings
	char strHealth[16];
	char strScore[16];
	char strLives[16];
	char strFPS[16];
	sprintf_s(strHealth, "Health: %i", m_Health);
	sprintf_s(strScore, "Score: %i", m_Score);
	sprintf_s(strLives, "Lives: %i", m_Lives);
	sprintf_s(strFPS, "FPS: %i", aie::Application::GetInstance()->GetFPS());

	// Draw GUI
	float xPos = xOrigin + BORDER;
	float yPos = yOrigin - BORDER;
	renderer->SetRenderColour(0xFFFFFFFF);
	renderer->DrawText2D(font, strHealth, xPos, yPos);			yPos -= PADDING;
	renderer->DrawText2D(font, strScore, xPos, yPos);			yPos -= PADDING;
	renderer->DrawText2D(font, strLives, xPos, yPos);			yPos -= PADDING;
	renderer->DrawText2D(font, strFPS, xPos, yPos);				yPos -= PADDING;
}

// Score setter functions
void GUI::SetHealth(int health)
{
	m_Health = health;
}
void GUI::SetScore(int score)
{
	m_Score = score;
}
void GUI::SetLives(int lives)
{
	m_Lives = lives;
}