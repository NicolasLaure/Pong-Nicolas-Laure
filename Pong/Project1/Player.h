#pragma once
#include "ExternalHeaders/raylib.h"
#include "ExternalHeaders/raymath.h"

struct Box 
{
	Vector2 position{};
	float height{};
	float width{};
};

struct Paddle
{
public:
	bool isPlayer1{};
	Box hitBox = { {}, 300, 25 };
	float speed = 1000;
};

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne);
void PlayerUpdate(Paddle& player);

void PlayerDraw(Paddle player);