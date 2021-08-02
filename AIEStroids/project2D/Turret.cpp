//
// Author: Keira 
//

#include "Turret.h"
#include <cmath>

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

	// -=-=- POSITION -=-=- To change where turret sits on 'player'
	// - ADJUSTABLE - Only change if turrets position is wrong.
	float xOffset = 0;
	float yOffset = 0;
	
	// -=-=- AESTHETIC -=-=- Just aesthetic things, these do not effect functionality.
	// - ADJUSTABLE - Where the "kick back" from firing moves turret (distance)
	m_kickBackPos = 0;
	// - ADJUSTABLE - Force turret is kicked back with
	m_kickBackForce = 50;

	// -=-=- END OF ADJUSTABLE VARIABLES -=-=-

	// -=-=- Other config stuff -=-=-

	// - DO NOT TOUCH - Waiting on other stuff to be completed  to uncomment
	//m_bWrapAndRespawn = false;
	//m_bVisible = true;

	// - DO NOT TOUCH - Automatically assigned based off fire rate
	m_timeBetweenBullets = 1/m_firerate;
	// - DO NOT TOUCH - Tracks time since last shot was fired - Leave at 0
	m_lastShotTimeDelta = m_timeBetweenBullets; //Makes it so firing is available as soon as loaded in,
										   //otherwise "Timebetweenbullets" time has to pass before firing if 0.
											

	// - DO NOT TOUCH - Position correction of turret on 'player'
	m_m3Offset.ResetToIdentity();
	m_m3Offset.SetPosition(xOffset, yOffset);

	m_input = aie::Input::GetInstance();

	//more initialization
	m_momentum = 0;
	m_rotation = 0;
	m_speed = 0;
	m_velocity = 0;

	//m_bulletManager = new BulletManager(/*Enter amount of bullets here, once functionality is added*/);
}

Turret::~Turret() {

};

void Turret::Update(float deltaTime) {
	Controller(deltaTime);
}

//void Turret::Draw() {
//
//}

Vector2 Turret::GetMousePos() {
	return Vector2((float)m_input->GetMouseX(), (float)m_input->GetMouseY());
}

bool Turret::IsLeftMouseClicked() {
	m_input->IsMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT);
}

void Turret::Controller(float deltaTime) {
	Rotate(deltaTime);
	Fire(deltaTime);
	TurretKickback(deltaTime);
}

void Turret::Rotate(float deltaTime) {
	Vector2 turretPos = m_globalTransform.GetPosition();
	Vector2 mousePos = GetMousePos();
	Vector2 diffPos = turretPos - mousePos;

	float mouseAngle = atan2(diffPos.y, diffPos.x);

	//should work, if it doesn't check here first
	float turretAngle = atan2(m_globalTransform.GetUp().y, m_globalTransform.GetUp().x);

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
		m_localTransform = m_localTransform * movement;
	}
}

void Turret::Fire(float deltaTime) {

	m_lastShotTimeDelta += deltaTime;

	if (IsLeftMouseClicked() && m_lastShotTimeDelta >= m_timeBetweenBullets) 
	{
		//Call BulletManager here to create a bullet -=-=- MISSING FUNCTION CALL HERE -=-=-
		
		//BulletManager->Shoot(m_globalTransform.GetPosition(), m_globalTransform.GetRotation());

		//Also move bullet forwards some amount so it doesn't spawn on top of the turret
		m_lastShotTimeDelta = 0;
	}

}

void Turret::TurretKickback(float deltaTime)
{
	//Might make value editable elsewhere
	//Max time for turret to return to normal position, after "kickback"
	float m_maxKBSettleTime = 0.5;


	//Moves turret towards normal position, if not in normal position
	float m_lastKickBackPos = m_kickBackPos;
	if (m_kickBackPos != 0) 
	{
		m_kickBackPos -= m_kickBackForce / fminf(m_timeBetweenBullets, m_maxKBSettleTime);
		//If overshoots turrets normal position, move to normal position
		if (m_kickBackPos < 0) 
		{
			m_kickBackPos = 0;
		}
	}

	//If m_lastShotTimeDelta = 0 (aka turret just fired), go to full kickback position
	if (m_lastShotTimeDelta == 0) 
	{
		m_kickBackPos = m_kickBackForce;
	}

	if (m_kickBackPos != 0) 
	{
		movement.ResetToIdentity();
		movement.SetPosition(0, m_kickBackPos);
		m_localTransform = m_localTransform * movement;
	}


}