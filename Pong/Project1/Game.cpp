#include "Game.h"
#include <iostream>
using namespace std;


void Initialize(GameData& gd);

void GameUpdate(GameData& gd);
void GameDraw(GameData gd);
void TableDraw(GameData gd);
void ScoreDraw(int score, Vector2 position);

void CollisionUpdate(GameData& gd);
void BallBorderCollision(GameData& gd);
void BallPaddleCollision(Ball& ball, Paddle& player);

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

	Vector2 player1Position = { static_cast<float>(GetScreenWidth() / 15),static_cast<float>(GetScreenHeight() / 2 - gd.player1.hitBox.height / 2) };
	PadInit(gd.player1, player1Position, true);
	Vector2 player2Position = { static_cast<float>(GetScreenWidth() - GetScreenWidth() / 15), static_cast<float>(GetScreenHeight() / 2 - gd.player2.hitBox.height / 2) };
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

void CollisionUpdate(GameData& gd)
{
	BallBorderCollision(gd);
	BallPaddleCollision(gd.ball, gd.player1);
	BallPaddleCollision(gd.ball, gd.player2);
}

void BallBorderCollision(GameData& gd)
{
	if (gd.ball.position.x < 0)
	{
		gd.ball.position = gd.ball.startPosition;
		gd.ball.speed = gd.ball.baseSpeed;
		gd.playerTwoScore++;
	}
	else if (gd.ball.position.x + gd.ball.size > GetScreenWidth())
	{
		gd.ball.position = gd.ball.startPosition;
		gd.ball.speed = gd.ball.baseSpeed;
		gd.playerOneScore++;
	}

	BallSwitchDirY(gd.ball);
}

void BallPaddleCollision(Ball& ball, Paddle& player)
{
	if (ball.hitBox.position.x + ball.hitBox.width >= player.hitBox.position.x
		&& ball.hitBox.position.x <= player.hitBox.position.x + player.hitBox.width
		&& ball.hitBox.position.y + ball.hitBox.height >= player.hitBox.position.y
		&& ball.hitBox.position.y <= player.hitBox.position.y + player.hitBox.height)
	{
		if (player.hitBox.position.x < GetScreenWidth() / 2)
		{
			if (ball.position.x > player.hitBox.position.x - (player.hitBox.width / 2))
				BallSwitchDirX(ball, player);
		}
		else
			if (ball.position.x < player.hitBox.position.x + (player.hitBox.width / 2))
				BallSwitchDirX(ball, player);

		//Tangente = Opuesto/Adyacente
		Vector2 hitPoint = { player.hitBox.position.x, ball.position.y + ball.size / 2 };
		float catetoOp = (player.hitBox.position.x + player.hitBox.width / 2) - hitPoint.x;
		float catetoAd = (player.hitBox.position.y + player.hitBox.height / 2) - hitPoint.y;
		//float catetoOp = (player.hitBox.position.y + player.hitBox.height / 2) - (ball.position.y + ball.size);

		//float angle = Vector2Angle(hitPoint, { player.hitBox.position.x + player.hitBox.width / 2, player.hitBox.position.y + player.hitBox.height / 2 });
		float angle = catetoOp / catetoAd;
		//float angle = tan(hitPoint, { player.hitBox.position.x + player.hitBox.width / 2, player.hitBox.position.y + player.hitBox.height / 2 });
		cout << angle << endl;
	}
}