#include "Rock.h"
#include "Application.h"
#include "TextureManager.h"
#include "CollisionLayers.h"
Rock::Rock(Player* player)
{
	_player = player;
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/rock_large.png");
	
	//--------- COLLIDER GENERATION ----------------------//
	//Create a box that is the same dimensions as the texture
	Shape* shape = PolygonShape::CreateBox(m_Texture->GetWidth() / 2.0f, m_Texture->GetHeight() / 2.0f, Vector2::ZERO());
	//Collide with everything
	unsigned int layermask = (unsigned int)CollisionLayer::ALL;
	//unsigned int layermask = 0;
	//Create collider
	Collider* collider = new Collider(shape, (unsigned short)CollisionLayer::ROCK, layermask);
	m_PhysicsBody = new PhysicsBody(this, BodyType::DYNAMIC, collider);
	
	SetRandomPath();
}

Rock::~Rock()
{

}

void Rock::OnCollision(CollisionEvent _event)
{
	if (_event.other->GetCollider()->GetCollisionLayer() == (unsigned short) CollisionLayer::BULLET) {
		health = health - 1;
		if (health == 0) {
			SetRandomPath();
			health = 5;
		}
	}
	
	
} 

void Rock::SetRandomPath()
{
	float scale = ((rand() % 30) / 10.0f) + 1;
	m_LocalTransform.SetScale(scale, scale);
	aie::Application* app = aie::Application::GetInstance();
	int edge = rand() % 4;
	int x = 0;
	int y = 0;
	switch (edge) {
	case 0:
		x = 0 - app->GetWindowWidth();
		y = rand() % app->GetWindowHeight();
		break;
	case 1:
		x = rand() % app->GetWindowWidth();
		y = app->GetWindowHeight() + app->GetWindowHeight();
		break;
	case 2:
		x = app->GetWindowWidth() + app->GetWindowWidth();
		y = rand() % app->GetWindowHeight();
		break;
	case 3:
		x = rand() % app->GetWindowWidth();
		y = 0 - app->GetWindowHeight();
		break;
	}
	
	Vector2 position(x + _player->GetPosition().x - app->GetWindowWidth()/2, y+ _player->GetPosition().y - app->GetWindowHeight() / 2);
	Vector2 direction(((rand() % 200) - 100) / 100.0f, ((rand() % 200) - 100) / 100.0f);
	SetPosition(position);
	SetRotation((rand() % 360) * DEG2RAD);
	m_PhysicsBody->SetVelocity(direction.GetNormalised() * (25 + (rand() % 50)));
	//m_PhysicsBody->SetVelocity(Vector2());
	m_PhysicsBody->SetAngularVelocity((rand() % 5)-2.5);
}
void Rock::Update(float deltaTime)
{
	aie::Application* app = aie::Application::GetInstance();
	if (abs(GetPosition().x - _player->GetPosition().x) > app->GetWindowWidth()*2) {
		SetRandomPath();
	}
	if (abs(GetPosition().y - _player->GetPosition().y) > app->GetWindowHeight()*2) {
		SetRandomPath();
	}
}