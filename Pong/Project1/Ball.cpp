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
	Vector2 dir = { 0,0 };
	switch (ball.dir)
	{
	case Directions::DownLeft:
		dir = { -1,1 };
		break;
	case Directions::DownRight:
		dir = { 1,1 };
		break;
	case Directions::UpLeft:
		dir = { -1,-1 };
		break;
	case Directions::UpRight:
		dir = { 1,-1 };
		break;
	default:
		break;
	}

	dir.x = dir.x * ball.speed * GetFrameTime();
	dir.y = dir.y * ball.speed * GetFrameTime();

	ball.position = Vector2Add(ball.position, dir);
	ball.hitBox.position = ball.position;
}

void BallDraw(Ball ball)
{
	DrawRectangle(ball.position.x, ball.position.y, ball.size, ball.size, WHITE);
}

