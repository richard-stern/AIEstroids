#include "Rock.h"
#include "Application.h"
#include "TextureManager.h"
Rock::Rock() : Actor()
{
	AddPhysicsBody(new PhysicsBody(this, BodyType::DYNAMIC));
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/rock_large.png");
	SetRandomPath();
}

Rock::~Rock()
{

}

void Rock::OnCollision(GameObject* other)
{
	SetRandomPath();
} 

void Rock::SetRandomPath()
{
	srand(time(NULL));
	aie::Application* app = aie::Application::GetInstance();
	int edge = rand() % 4;
	int x = 0;
	int y = 0;
	switch (edge) {
	case 0:
		x = 0;
		y = rand() % app->GetWindowHeight();
		break;
	case 1:
		x = rand() % app->GetWindowWidth();
		y = app->GetWindowHeight();
		break;
	case 2:
		x = app->GetWindowWidth();
		y = rand() % app->GetWindowHeight();
		break;
	case 3:
		x = rand() % app->GetWindowWidth();
		y = 0;
		break;
	}
	Vector2 position(x, y);
	SetLocalPosition(position);
	m_PhysicsBody->SetVelocity(Vector2::ONE());
	m_PhysicsBody->SetAngularVelocity(1);
}
void Rock::Update(float deltaTime)
{
}