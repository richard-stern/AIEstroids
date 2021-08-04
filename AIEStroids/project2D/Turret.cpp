//
// Author: Keira 
//

//If CENTER_SCREEN will aim turret based off center of screen rather then turret pos, due to needing camera coords to use turret pos.
//#define CENTER_SCREEN

//Shooting currently throws an exception in Bullet.cpp, change from DISABLE_SHOOTING to ENABLE_SHOOTING to test it.
#define ENABLE_SHOOTING

#include "Turret.h"
#include "TextureManager.h"
#include <cmath>
#include "Camera.h"
//#include <iostream>

Turret::Turret() {

	// -=-=- ADJUSTABLE VARIABLES -=-=- all values are floats unless stated otherwise

	// -=-=- FUNCTIONALITY -=-=-

	// -=-=- TURRET MOVEMENT -=-=-
	// - ADJUSTABLE - Turret rotate speed
	m_rotateSpeed = 50;
	// - ADJUSTABLE - How fast turret stops moving
	m_rotateFriction = 10;
	// - ADJUSTABLE - turret speed up/slow down?
	m_mass = 1;

	// -=-=- FIRE RATE -=-=-
	// - ADJUSTABLE - Self explanatory, fire rate of turret, bullets per second
	m_firerate = 5;

	// -=-=- POSITION -=-=-
	// - ADJUSTABLE - Change turrets pivot
	m_fxOffset = 0;
	m_fyOffset = 0;
	
	// -=-=- AESTHETIC -=-=- Just aesthetic things, these do not effect functionality.
	// - ADJUSTABLE - Where the "kick back" from firing moves turret (distance)
	m_kickBackPos = 0;
	// - ADJUSTABLE - Force turret is kicked back with
	m_kickBackForce = 3;

	// -=-=- END OF ADJUSTABLE VARIABLES -=-=-

	// -=-=- Other config stuff -=-=-

	//Assign turret texture
	m_Texture = TextureManager::Get()->LoadTexture("../bin/sprites/Turrets.png");

	// - DO NOT TOUCH - Waiting on other stuff to be completed  to uncomment
	m_WrapAndRespawn = false; //Should be m_bWarpAndRespawn >:(
	//m_Visible = true;
	

	// - DO NOT TOUCH - Automatically assigned based off fire rate
	m_timeBetweenBullets = 1/m_firerate;
	// - DO NOT TOUCH - Tracks time since last shot was fired - Leave at 0
	m_lastShotTimeDelta = m_timeBetweenBullets; //Makes it so firing is available as soon as loaded in,
										        //otherwise "Timebetweenbullets" time has to pass before firing if 0.
											


	//Get input manager
	m_input = aie::Input::GetInstance();

	//more initialization
	m_momentum = 0;
	m_rotation = 0;
	m_speed = 0;
	m_velocity = 0;

	// - DO NOT TOUCH - Position correction of turret on 'player'
	m_m3Offset.ResetToIdentity();
	m_m3Offset.SetPosition(m_fxOffset, m_fyOffset);
	m_m3OffsetNeg.SetPosition(-m_fxOffset, -m_fyOffset);
	//m_LocalTransform = m_LocalTransform * m_m3Offset;

	//Sprite layer
	SetSpriteDepth(-1);

	m_bulletManager = new BulletManager(); /*Enter amount of bullets here, once functionality is added*/
}

Turret::~Turret() {
	delete (m_bulletManager);

};

void Turret::Update(float deltaTime) {
	Controller(deltaTime);
}



Vector2 Turret::GetCameraPos() 
{
	return Camera::GetInstance()->GetPosition();
}


void Turret::Draw(aie::Renderer2D* _renderer2D)
{
	GameObject::Draw(_renderer2D);
	m_bulletManager->Draw(_renderer2D);
}

Vector2 Turret::GetMousePos() {
	return Vector2((float)m_input->GetMouseX(), (float)m_input->GetMouseY());
}

bool Turret::IsLeftMouseClicked() {
	return m_input->IsMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT);
}

void Turret::Controller(float deltaTime) {
	Rotate(deltaTime);
	m_bulletManager->Update(deltaTime);
	Fire(deltaTime);
	TurretKickback(deltaTime);
}

void Turret::Rotate(float deltaTime) {
	Vector2 turretPos = m_GlobalTransform.GetPosition();
#ifdef CENTER_SCREEN
	turretPos = Vector2(aie::Application::GetInstance()->GetWindowWidth() / 2, aie::Application::GetInstance()->GetWindowHeight() / 2);
#endif

	Vector2 mousePos = GetMousePos() + GetCameraPos();
	Vector2 diffPos = turretPos - mousePos;


	float directionFix = M_PI / 2;


	float mouseAngle = atan2(diffPos.y, diffPos.x);

	//should work, if it doesn't check here first
	float turretAngle = atan2(m_GlobalTransform.GetUp().y, m_GlobalTransform.GetUp().x) + directionFix;

	if (turretAngle > 1 * M_PI) {
		turretAngle -= 2 * M_PI;
	}

	float rotate = mouseAngle - turretAngle;

	if (rotate > M_PI || rotate < -M_PI)
	{
		rotate *= -1;
	}

	//How close to get to 'perfect'
	//Higher - less accurate less jitter. Lower = more accurate more jitter
	float varience = 0.001;

	if (rotate < -varience)
	{
		m_rotation -= m_rotateSpeed * deltaTime / m_mass;
	}
	else if (rotate > varience)
	{
		m_rotation += m_rotateSpeed * deltaTime / m_mass;
	}
	if (rotate < 0.008 && rotate > -0.008)
	{
		//To try and stop jittering.. right? might remove if I find a good "varience" value
		m_rotation *= 0.8f;
	}

	if (m_rotation != 0)
	{
		//Apply friction to slow down
		m_rotation -= m_rotation * m_rotateFriction * deltaTime;

		movement.ResetToIdentity();
		movement.SetRotateZ(m_rotation * deltaTime);
		m_LocalTransform = m_LocalTransform * m_m3OffsetNeg;
		m_LocalTransform = m_LocalTransform * movement;
		m_LocalTransform = m_LocalTransform * m_m3Offset;
	}
}

void Turret::Fire(float deltaTime) {

	m_lastShotTimeDelta += deltaTime;

	if (IsLeftMouseClicked() && m_lastShotTimeDelta >= m_timeBetweenBullets) 
	{
		//Call BulletManager here to create a bullet -=-=- MISSING FUNCTION CALL HERE -=-=-
		
#ifdef ENABLE_SHOOTING
		m_bulletManager->ShootBullet(m_GlobalTransform.GetPosition(), m_GlobalTransform.GetRotation());
#endif
		//Also move bullet forwards some amount so it doesn't spawn on top of the turret
		m_lastShotTimeDelta = 0;
	}

}

void Turret::TurretKickback(float deltaTime)
{
	//Might make value editable elsewhere
	//Max time for turret to return to normal position, after "kickback"
	float m_maxKBSettleTime = 0.5;

	//If m_lastShotTimeDelta = 0 (aka turret just fired), go to full kickback position
	if (m_lastShotTimeDelta == 0) 
	{
		m_kickBackPos = m_kickBackForce;
	}

	//Moves turret towards normal position, if not in normal position
	float m_lastKickBackPos = m_kickBackPos;
	if (m_kickBackPos > 0) 
	{
		m_kickBackPos -= __max((m_kickBackForce - m_timeBetweenBullets) * deltaTime * m_firerate, (m_kickBackForce - m_timeBetweenBullets) * deltaTime * 2);

		//If overshoots turrets normal position, move to normal position
		if (m_kickBackPos < 0) 
		{
			m_kickBackPos = 0;
		}
	}

	if (m_kickBackPos != 0) 
	{
		//Will counter previous movement
		Vector2 fPrev = prevMovement.GetPosition();
		prevMovement.SetPosition(-fPrev);

		movement.ResetToIdentity();
		movement.SetPosition(-m_kickBackPos, 0.0f);
		m_LocalTransform = m_LocalTransform * movement * prevMovement;

		//Saves what movement last was
		prevMovement = movement;

	}


}