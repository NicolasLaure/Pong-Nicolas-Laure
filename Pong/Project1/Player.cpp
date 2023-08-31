#include "Player.h"

void PlayerUpdate(Paddle& player)
{

	if (player.isPlayer1)
	{

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
