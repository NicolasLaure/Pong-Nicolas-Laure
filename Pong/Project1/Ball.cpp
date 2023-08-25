#include "Ball.h"

void BallInit(Ball& ball)
{
	ball.startPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight() / 2 - ball.size / 2) };
	ball.position = ball.startPosition;
	ball.hitBox.height = ball.size;
	ball.hitBox.width = ball.size;
	ball.hitBox.position = ball.position;
}

void BallUpdate(Ball& ball)
{
	ball.position = Vector2Add(ball.position, Vector2Scale(ball.dir, ball.speed * GetFrameTime()));
	ball.hitBox.position = ball.position;
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
	ball.position.x -= player.hitBox.position.x - ball.position.x;
	ball.dir.x *= -1;
	if (ball.speed + 20 <= ball.maxSpeed)
		ball.speed += 20;
}

