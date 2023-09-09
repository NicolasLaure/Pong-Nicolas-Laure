#include "Objects/Player.h"

void PlayerUpdate(Paddle& player)
{

	if (player.isPlayer1)
	{
		if (IsKeyDown(KEY_W))
			PadMove(player, { 0, -1 });
		else if (IsKeyDown(KEY_S))
			PadMove(player, { 0, 1 });
	}
	else
	{
		if (IsKeyDown(KEY_UP))
			PadMove(player, { 0, -1 });
		else if (IsKeyDown(KEY_DOWN))
			PadMove(player, { 0, 1 });
	}
}
