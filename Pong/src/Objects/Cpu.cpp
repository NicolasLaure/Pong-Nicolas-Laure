#include "Objects/Cpu.h"

void CpuUpdate(Paddle& paddle, Ball ball)
{
	if (paddle.hitBox.position.y + paddle.hitBox.height / 2 >= ball.position.y + ball.size / 2)
		paddle.hitBox.position.y -= paddle.speed * 0.25f * GetFrameTime();
	else if (paddle.hitBox.position.y + paddle.hitBox.height / 2 < ball.position.y + ball.size / 2)
		paddle.hitBox.position.y += paddle.speed * 0.25f * GetFrameTime();

	if (paddle.hitBox.position.y <= 0)
		paddle.hitBox.position.y = 0;

	if (paddle.hitBox.position.y + paddle.hitBox.height >= GetScreenHeight())
		paddle.hitBox.position.y = GetScreenHeight() - paddle.hitBox.height;
}