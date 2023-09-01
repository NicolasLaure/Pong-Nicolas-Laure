#pragma once
#include "Paddle.h"
#include "Ball.h"

enum class PowerUpType
{
	FireBall,
	SlowDown,
	SpeedBoost,
	Count
};

struct PowerUp
{
	Vector2 position{ 0,0 };
	float size = 50;
	PowerUpType type{ PowerUpType::FireBall };
	Color color{ WHITE };
};

void FireBall(Ball& ball);

void SpeedBoost(Paddle& paddle, float& activeModifierTimer);

void SlowDown(Paddle& paddle, float& activeModifierTimer);

void ResetBall(Ball& ball);

void SetPowerUp(PowerUp& powerUp, Vector2 newPos);

void ResetPlayer(Paddle& paddle);

void PowerUpDraw(PowerUp& powerUp);
