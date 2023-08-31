#pragma once
#include "Utilities.h"

struct Paddle
{
public:
	bool isPlayer1{};
	Rect hitBox = { {}, 200, 25 };
	float baseSpeed = 1000;
	float speed = 1000;
};

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne);
void PaddleDraw(Paddle player);