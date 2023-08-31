#include "PowerUps.h"

void FireBall(Ball& ball)
{
	ball.prevSpeed = ball.speed;
	ball.speed = 1400;
	ball.color = RED;
}

void SpeedBoost(Paddle& paddle, float& activeModifierTimer)
{
	float speedBoostDuration = 3;

	activeModifierTimer = GetTime() + speedBoostDuration;
	paddle.speed *= 1.4f;
}
void SlowDown(Paddle& paddle, float& activeModifierTimer)
{
	float slowDownDuration = 3;

	activeModifierTimer = GetTime() + slowDownDuration;
	paddle.speed *= 0.75f;
}

void ResetBall(Ball& ball)
{
	ball.color = WHITE;
	ball.speed = ball.prevSpeed;
}

void ResetPlayer(Paddle& paddle)
{
	paddle.speed = paddle.baseSpeed;
}
