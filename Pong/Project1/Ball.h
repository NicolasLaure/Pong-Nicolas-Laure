#pragma once
#include "Player.h"

enum class Directions {
	UpLeft,
	UpRight,
	DownLeft,
	DownRight
};

struct Ball
{
public:

	Box hitBox;
	Vector2 position{};
	Vector2 startPosition{};
	float size = 25;
	Directions dir{ Directions::DownRight };
	float speed = 500;
};

void BallInit(Ball& ball);
void BallUpdate(Ball& ball);

void BallDraw(Ball ball);
