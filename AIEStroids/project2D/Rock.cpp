#include "Rock.h"
#include "Application.h"
#include "TextureManager.h"
#include "CollisionLayers.h"
Rock::Rock() : Actor()
{
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/rock_large.png");
	//--------- COLLIDER GENERATION ----------------------//
	//Create a box that is the same dimensions as the texture
	Shape* shape = PolygonShape::CreateBox(m_Texture->GetWidth() / 2.0f, m_Texture->GetHeight() / 2.0f, Vector2::ZERO());
	//Collide with everything
	unsigned int layermask = (unsigned int)CollisionLayer::ALL;
	//Create collider
	Collider* collider = new Collider(shape, (unsigned short)CollisionLayer::ROCK, layermask);
	m_PhysicsBody = new PhysicsBody(this, BodyType::DYNAMIC, collider);
	
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
	SetPosition(position);
	m_PhysicsBody->SetVelocity(Vector2::ONE()* 50);
	m_PhysicsBody->SetAngularVelocity(1);
}
void Rock::Update(float deltaTime)
{
}