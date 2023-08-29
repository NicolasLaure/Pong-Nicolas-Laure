#include "Game.h"
#include <cmath>


void Game(GameData& gd);
void GameStart(GameData& gd);
void GameUpdate(GameData& gd);
void GameDraw(GameData gd);

void TableDraw(GameData gd);
void ScoreDraw(int score, Vector2 position);

void CollisionUpdate(GameData& gd);
void BallBorderCollision(GameData& gd);
void BallPaddleCollision(Ball& ball, Paddle& player);

void Game(GameData& gd)
{
	if (gd.enteredNewScene)
		GameStart(gd);

	GameUpdate(gd);
	GameDraw(gd);
}
void GameStart(GameData& gd)
{
	Vector2 player1Position = { static_cast<float>(GetScreenWidth() / 15),static_cast<float>(GetScreenHeight() / 2 - gd.player1.hitBox.height / 2) };
	PadInit(gd.player1, player1Position, true);
	Vector2 player2Position = { static_cast<float>(GetScreenWidth() - GetScreenWidth() / 15), static_cast<float>(GetScreenHeight() / 2 - gd.player2.hitBox.height / 2) };
	PadInit(gd.player2, player2Position, false);
	BallInit(gd.ball);
}
void GameUpdate(GameData& gd)
{
	PlayerUpdate(gd.player1);
	if (!gd.isSinglePlayer)
		PlayerUpdate(gd.player2);

	if (gd.playerOneScore >= 7 || gd.playerTwoScore >= 7)
	{
		if (gd.playerOneScore >= 7)
			gd.player1HasWon = true;

		gd.scene = Scenes::GameOver;
	}
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
	if (ball.position.x + ball.size >= player.hitBox.position.x
		&& ball.position.x <= player.hitBox.position.x + player.hitBox.width
		&& ball.position.y + ball.size >= player.hitBox.position.y
		&& ball.position.y <= player.hitBox.position.y + player.hitBox.height)
	{
		ball.position.x -= player.hitBox.position.x - ball.position.x;
		Vector2 hitPoint = { player.hitBox.position.x, ball.position.y + ball.size / 2 };

		float angle = 0;
		float angleModifier = 30;
		float straightShotPercentage = 0.4f;
		if (ball.dir.x > 0 && ball.position.x < player.hitBox.position.x + player.hitBox.width)
			angle = 180 - ((player.hitBox.position.y + player.hitBox.height / 2) - hitPoint.y) / ((player.hitBox.position.x + player.hitBox.width / 2) - hitPoint.x);
		else if (ball.dir.x < 0 && ball.position.x > player.hitBox.position.x)
			angle = 360 - ((player.hitBox.position.y + player.hitBox.height / 2) - hitPoint.y) / ((player.hitBox.position.x + player.hitBox.width / 2) - hitPoint.x);

		if (hitPoint.y <= player.hitBox.position.y + player.hitBox.height * straightShotPercentage || hitPoint.y >= player.hitBox.position.y + player.hitBox.height * (1 - straightShotPercentage))
		{
			if (angle > 360 || angle < 180)
				angle -= angleModifier;
			else
				angle += angleModifier;
		}

		ball.dir = { cos(angle * DEG2RAD), sin(angle * -1 * DEG2RAD) };

		if (ball.speed + ball.speedIncrement < ball.maxSpeed)
			ball.speed += ball.speedIncrement;
	}
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