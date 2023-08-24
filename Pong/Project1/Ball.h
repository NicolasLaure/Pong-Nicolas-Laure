#pragma once
#include "Player.h"

struct Ball
{
public:

	Box hitBox;
	Vector2 position{};
	Vector2 startPosition{};
	Vector2 dir = {1,1};
	float size = 25;
	float baseSpeed = 500;
	float speed = 500;
	float maxSpeed = 750;
};

void BallInit(Ball& ball);
void BallUpdate(Ball& ball);

void BallDraw(Ball ball);
