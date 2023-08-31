#pragma once
#include "Paddle.h"
#include "Ball.h"

enum class PowerUpType
{
	FireBall,
	SlowDown,
	SpeedBoost
};

struct PowerUp
{
	Vector2 position{ 0,0 };
	float size;
	PowerUpType type{ PowerUpType::FireBall };
	Color color{ WHITE };
};

void FireBall(Ball& ball);

void SpeedBoost(Paddle& paddle, float& activeModifierTimer);

void SlowDown(Paddle& paddle, float& activeModifierTimer);

void ResetBall(Ball& ball);

void ResetPlayer(Paddle& paddle);
