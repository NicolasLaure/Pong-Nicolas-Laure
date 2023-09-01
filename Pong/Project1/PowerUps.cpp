#include "PowerUps.h"

void FireBall(Ball& ball)
{
	ball.prevSpeed = ball.speed;
	ball.speed = 1400;
	ball.color = RED;
}

void SpeedBoost(Paddle& paddle, float& activeModifierTimer)
{
	float speedBoostDuration = 5;

	paddle.isModified = true;
	paddle.color = PURPLE;
	activeModifierTimer = GetTime() + speedBoostDuration;
	paddle.speed *= 1.8f;
}
void SlowDown(Paddle& paddle, float& activeModifierTimer)
{
	float slowDownDuration = 1.5;

	paddle.isModified = true;
	paddle.color = SKYBLUE;
	activeModifierTimer = GetTime() + slowDownDuration;
	paddle.speed *= 0.6f;
}

void ResetBall(Ball& ball)
{
	ball.color = WHITE;
	ball.speed = ball.prevSpeed;
}

void ResetPlayer(Paddle& paddle)
{
	paddle.isModified = false;
	paddle.color = LIGHTGRAY;
	paddle.speed = paddle.baseSpeed;
}

void SetPowerUp(PowerUp& powerUp, Vector2 newPos)
{
	powerUp.type = static_cast<PowerUpType>(GetRandomValue(0, static_cast<int>(PowerUpType::Count) - 1));
	powerUp.position = newPos;
	switch (powerUp.type)
	{
	case PowerUpType::FireBall:
		powerUp.color = RED;
		break;
	case PowerUpType::SlowDown:
		powerUp.color = SKYBLUE;
		break;
	case PowerUpType::SpeedBoost:
		powerUp.color = PURPLE;
		break;
	default:
		break;
	}
}
void PowerUpDraw(PowerUp& powerUp)
{
	DrawRectangle(powerUp.position.x, powerUp.position.y, powerUp.size, powerUp.size, powerUp.color);
}