#include "Ball.h"

void BallInit(Ball& ball)
{
	ball.startPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight() / 2 - ball.size / 2) };
	ball.position = ball.startPosition;
	float value = 0;
	value = GetRandomValue(-5, 5) * 0.1f;
	if (value <= 0.3f && value >= 0) value = 0.3f;
	if (value >= -0.3f && value < 0) value = -0.3f;
	float randX = value;
	if (GetRandomValue(0, 1) == 0)
	{
		if (value < 0)
			value = value * -1 - 1;
		else
			value -= 1.0f;
	}
	else
	{
		if (value < 0)
			value += 1.0f;
		else
			value = 1.0f - value;
	}
	float randY = value;
	ball.dir = { randX, randY };
}

void BallUpdate(Ball& ball)
{
	ball.position = Vector2Add(ball.position, Vector2Scale(ball.dir, ball.speed * GetFrameTime()));
}

void BallDraw(Ball ball)
{
	DrawRectangle(ball.position.x, ball.position.y, ball.size, ball.size, WHITE);
}


void BallSwitchDirY(Ball& ball)
{
	if (ball.position.y <= 0)
	{
		ball.position.y = 0;
		ball.dir.y *= -1;
	}
	else if (ball.position.y + ball.size >= GetScreenHeight())
	{
		ball.position.y = GetScreenHeight() - ball.size;
		ball.dir.y *= -1;
	}
}

void BallSwitchDirX(Ball& ball, Paddle player)
{
	ball.dir.x *= -1;
	if (ball.speed + 20 <= ball.maxSpeed)
		ball.speed += 20;
}

