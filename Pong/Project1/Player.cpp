#include "Player.h"

void PadInit(Paddle& paddle, Vector2 position, bool isPlayerOne)
{
	paddle.hitBox.position.x = position.x;
	paddle.hitBox.position.y = position.y;
	paddle.isPlayer1 = isPlayerOne;
}

void PlayerUpdate(Paddle& player) {

	if (player.isPlayer1) {

		if (IsKeyDown(KEY_W))
			player.hitBox.position.y -= player.speed * GetFrameTime();
		else if (IsKeyDown(KEY_S))
			player.hitBox.position.y += player.speed * GetFrameTime();
	}
	else
	{
		if (IsKeyDown(KEY_UP))
			player.hitBox.position.y -= player.speed * GetFrameTime();
		else if (IsKeyDown(KEY_DOWN))
			player.hitBox.position.y += player.speed * GetFrameTime();
	}

	if (player.hitBox.position.y <= 0)
		player.hitBox.position.y = 0;

	if (player.hitBox.position.y + player.hitBox.height >= GetScreenHeight())
		player.hitBox.position.y = GetScreenHeight() - player.hitBox.height;

}

void PlayerDraw(Paddle player) 
{
	DrawRectangle(player.hitBox.position.x, player.hitBox.position.y, player.hitBox.width, player.hitBox.height, LIGHTGRAY);
}