#include "Ball.h"

void BallInit(Ball& ball)
{
	ball.startPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
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

