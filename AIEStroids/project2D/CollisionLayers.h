#pragma once

enum class CollisionLayer : unsigned short
{
	PLAYER = 0b1,
	ROCK = 0b10,
	BULLET = 0b100,
	PICKUP = 0b1000,
	ENEMY = 0b10000,
	ALL = 0xFF
};