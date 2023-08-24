#include "Game.h"


void RunGame()
{
	GameData gd;
	Initialize(gd);

	while (!WindowShouldClose())
	{
		//Update
		GameUpdate(gd);

		//Draw
		GameDraw(gd);
	}

	CloseWindow();
}
void Initialize(GameData& gd)
{
	InitWindow(1280, 720, "Prototipo");

	Vector2 player1Position = { static_cast<float>(GetScreenWidth() / 15),static_cast<float>(GetScreenHeight() / 2) };
	PadInit(gd.player1, player1Position, true);
	Vector2 player2Position = { static_cast<float>(GetScreenWidth() - GetScreenWidth() / 15),static_cast<float>(GetScreenHeight() / 2) };
	PadInit(gd.player2, player2Position, false);
	BallInit(gd.ball);
}

void GameUpdate(GameData& gd)
{
	PlayerUpdate(gd.player1);
	PlayerUpdate(gd.player2);
	BallUpdate(gd.ball);
	CollisionUpdate(gd);
}

void GameDraw(GameData gd)
{
	BeginDrawing();
	ClearBackground(BLACK);

	TableDraw(gd);
	PlayerDraw(gd.player1);
	PlayerDraw(gd.player2);
	BallDraw(gd.ball);

	EndDrawing();
}

void TableDraw(GameData gd)
{
	int limitWidth = 5;
	DrawRectangle(0, 0, GetScreenWidth(), limitWidth, LIGHTGRAY);
	DrawRectangle(0, 0, limitWidth, GetScreenHeight(), LIGHTGRAY);
	DrawRectangle(GetScreenWidth() / 2, 0, limitWidth, GetScreenHeight(), LIGHTGRAY);
	DrawRectangle(0, GetScreenHeight() - limitWidth, GetScreenWidth(), limitWidth, LIGHTGRAY);
	DrawRectangle(GetScreenWidth() - limitWidth, 0, limitWidth, GetScreenHeight(), LIGHTGRAY);

	Vector2 score1 = { GetScreenWidth() / 3, GetScreenHeight() / 6 };
	Vector2 score2 = { GetScreenWidth() - GetScreenWidth() / 3 - 50, GetScreenHeight() / 6 };
	ScoreDraw(gd.playerOneScore, score1);
	ScoreDraw(gd.playerTwoScore, score2);

}

void ScoreDraw(int score, Vector2 position)
{
	DrawText(TextFormat("%01i", score), position.x, position.y, 150, LIGHTGRAY);
}

bool BallPaddleCollision(Box ballHitBox, Box paddleBox)
{
	return (ballHitBox.position.x + ballHitBox.width >= paddleBox.position.x && ballHitBox.position.x <= paddleBox.position.x + paddleBox.width && ballHitBox.position.y + ballHitBox.height >= paddleBox.position.y && ballHitBox.position.y <= paddleBox.position.y + paddleBox.height);
}

void CollisionUpdate(GameData& gd)
{
	if (gd.ball.position.x < 0)
	{
		gd.ball.position = gd.ball.startPosition;
		gd.playerTwoScore++;
	}
	else if (gd.ball.position.x + gd.ball.size > GetScreenWidth())
	{
		gd.ball.position = gd.ball.startPosition;
		gd.playerOneScore++;
	}

	if (gd.ball.position.y <= 0)
	{
		if (gd.ball.dir == Directions::UpLeft)
			gd.ball.dir = Directions::DownLeft;
		else if (gd.ball.dir == Directions::UpRight)
			gd.ball.dir = Directions::DownRight;
	}
	else if (gd.ball.position.y + gd.ball.size >= GetScreenHeight())
	{
		if (gd.ball.dir == Directions::DownLeft)
			gd.ball.dir = Directions::UpLeft;
		else if(gd.ball.dir == Directions::DownRight)
			gd.ball.dir = Directions::UpRight;
	}

	if (BallPaddleCollision(gd.ball.hitBox, gd.player1.hitBox))
	{
		if (gd.ball.dir == Directions::DownLeft)
			gd.ball.dir = Directions::DownRight;
		else if (gd.ball.dir == Directions::UpLeft)
			gd.ball.dir = Directions::UpRight;
	}
	else if (BallPaddleCollision(gd.ball.hitBox, gd.player2.hitBox))
	{
		if (gd.ball.dir == Directions::DownRight)
			gd.ball.dir = Directions::DownLeft;
		else if (gd.ball.dir == Directions::UpRight)
			gd.ball.dir = Directions::UpLeft;
	}
}