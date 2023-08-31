#include "Paddle.h"

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne)
{
	paddle.hitBox.position.x = position.x;
	paddle.hitBox.position.y = position.y;
	paddle.isPlayer1 = isPlayerOne;
}

void PaddleDraw(Paddle paddle) 
{
	DrawRectangle(paddle.hitBox.position.x, paddle.hitBox.position.y, paddle.hitBox.width, paddle.hitBox.height, LIGHTGRAY);
}