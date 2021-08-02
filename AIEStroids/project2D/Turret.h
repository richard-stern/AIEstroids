//
// Author: Matin Kamali
//

#pragma once
#include "Actor.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "Input.h"

class Turret :
	public Actor
{

public:

	//Done for now - Need parts from other people (Texture import, setting parent, etc)
	Turret();

	//Empty
	~Turret();

	//Empty
	void Update();

	//Empty
	void Draw();

private:

	// -=-=- PLAYER INPUT FUNCTIONS -=-=-
	//returns mouse pos
	Vector2 GetMousePos();
	//returns if mouse is clicked
	bool IsLeftMouseClicked();

	
	//controller, changes variables based on player input
	void Controller(float deltaTime);
	void Rotate(float deltaTime);
	void Fire(float deltaTime);

	//Aesthetic targetted function, moves turret back and forth
	void TurretKickback(float deltaTime); 

	//Visual Aesthetic stuff
	//Position of turret offset from 'player'
	Matrix3 m_m3Offset;
	//Where the "kick back" from firing moves turret (distance)
	float m_kickBackPos;
	//Force turret is kicked back with
	float m_kickBackForce;

	//Self explanatory, fire rate of turret
	float m_firerate;
	//Automatically assigned based off fire rate
	float m_timeBetweenBullets;
	//Tracks time since last shot was fired
	float m_lastShotTimeDelta;

	//Turret control variables - Adjustable
	//How fast the turret can rotate (Probably per second, full rotation = 360, will update if I make sure this is how it works)
	float m_rotateSpeed;
	//How fast turret stops moving
	float m_rotateFriction;
	//turret speed up/slow down?
	float m_mass;

	//Turret Movement Variables
	Vector2 m_posChange;
	float m_speed;
	float m_momentum;
	float m_rotation;
	float m_velocity;

	//Hopefully temporary vars that will be in gameobject/actor once implemented
	//GameObject m_parent;
	Matrix3 m_globalTransform;
	Matrix3 m_localTransform;


	aie::Input* m_input;

};

