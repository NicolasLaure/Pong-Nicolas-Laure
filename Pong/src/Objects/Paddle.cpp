#include "Objects/Paddle.h"

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne)
{
	paddle.hitBox.position.x = position.x;
	paddle.hitBox.position.y = position.y;
	paddle.isPlayer1 = isPlayerOne;
}

void PadMove(Paddle& paddle, Vector2 dir)
{
	if (paddle.hitBox.position.y >= 0 && paddle.hitBox.position.y + paddle.hitBox.height <= GetScreenHeight())
		paddle.hitBox.position = Vector2Add(paddle.hitBox.position, Vector2Scale(dir, paddle.speed * GetFrameTime()));
	else if (paddle.hitBox.position.y < 0)
		paddle.hitBox.position.y = 0;
	else if (paddle.hitBox.position.y + paddle.hitBox.height > GetScreenHeight())
		paddle.hitBox.position.y = GetScreenHeight() - paddle.hitBox.height;
}

void PaddleDraw(Paddle paddle)
{
	DrawRectangle(paddle.hitBox.position.x, paddle.hitBox.position.y, paddle.hitBox.width, paddle.hitBox.height, paddle.color);
}