//
// Author: Keira
//

#pragma once
#include "Actor.h"
#include "Vector2.h"
#include "Matrix3.h"
#include "Input.h"
#include "BulletManager.h"


class Turret :
	public Actor
{

public:

	//Done for now - Need parts from other people (Texture import, setting parent, etc)
	Turret();

	//Deletes bullet manager
	~Turret();

	//Empty
	void Update(float deltaTime);

	void SetPos(float x, float y);

	//Empty
	void Draw(aie::Renderer2D* _renderer2D) override;

private:

	// -=-=- PLAYER INPUT FUNCTIONS -=-=-
	//returns mouse pos
	Vector2 GetMousePos();
	//returns if mouse is clicked
	bool IsLeftMouseClicked();

	//Camera position input
	Vector2 GetCameraPos();
	
	//controller, changes variables based on player input
	void Controller(float deltaTime);
	void Rotate(float deltaTime);
	void Fire(float deltaTime);


	//Aesthetic targetted function, moves turret back and forth
	void TurretKickback(float deltaTime); 

	//Visual Aesthetic stuff
	float m_SShakeDuration;
	float m_SShakeForce;

	//Change pivot maybe;
	Matrix3 m_m3Offset;
	Matrix3 m_m3OffsetNeg;
	float m_fxOffset;
	float m_fyOffset;

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
	Matrix3 movement;
	Matrix3 prevMovement;
	Vector2 m_posChange;
	float m_speed;
	float m_momentum;
	float m_rotation;
	float m_velocity;

	//Hopefully temporary vars that will be in gameobject/actor once implemented
	//GameObject m_parent;
	//Matrix3 m_globalTransform;
	//Matrix3 m_localTransform;

	//For input stuff, obv.
	aie::Input* m_input;

	//Bullet manager
	BulletManager* m_bulletManager;

};