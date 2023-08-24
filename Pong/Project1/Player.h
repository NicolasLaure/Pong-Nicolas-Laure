#pragma once
#include "Utilities.h"

struct Paddle
{
public:
	bool isPlayer1{};
	Box hitBox = { {}, 200, 25 };
	float speed = 1000;
};

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne);
void PlayerUpdate(Paddle& player);

void PlayerDraw(Paddle player);