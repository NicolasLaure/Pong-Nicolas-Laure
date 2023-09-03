#include "Game.h"
#include <cmath>

using namespace game;

static GameData gd;

void GameStart(bool isSinglePlayer);
void GameUpdate();
void GameDraw();

void ResetGameStats();

void PauseUpdate(Scenes& scene);
void PauseDraw();

void TableDraw();
void ScoreDraw(int score, Vector2 position);

void CollisionUpdate();
void BallBorderCollision();
void BallPaddleCollision(Ball& ball, Paddle& player);
void BallPowerUpCollision();

void PickPowerUp();

void game::GameLoop(bool enteredNewScene, Scenes& scene, bool isSinglePlayer)
{

	if (enteredNewScene || gd.justRestarted)
	{
		GameStart(isSinglePlayer);
		gd.justRestarted = false;
	}
	
	if (!gd.isPaused)
	{
		GameUpdate();
		GameDraw();
	}
	else
	{
		PauseUpdate(scene);
		PauseDraw();
	}
}
void GameStart(bool isSinglePlayer)
{
	gd.isSinglePlayer = isSinglePlayer;
	ResetGameStats();

	Vector2 player1Position = { static_cast<float>(GetScreenWidth() / 15),static_cast<float>(GetScreenHeight() / 2 - gd.player1.hitBox.height / 2) };
	PadInit(gd.player1, player1Position, true);
	Vector2 player2Position = { static_cast<float>(GetScreenWidth() - GetScreenWidth() / 15), static_cast<float>(GetScreenHeight() / 2 - gd.player2.hitBox.height / 2) };
	PadInit(gd.player2, player2Position, false);
	BallInit(gd.ball);
}
void GameUpdate()
{
	PlayerUpdate(gd.player1);
	if (!gd.isSinglePlayer)
		PlayerUpdate(gd.player2);
	else
		CpuUpdate(gd.player2, gd.ball);

	if (IsKeyPressed(KEY_ESCAPE))
	{
		if (!gd.isPaused)
			gd.isPaused = true;
		else
			gd.isPaused = false;
	}

	if (!gd.isSinglePlayer && !gd.isPowerUpSpawned && GetTime() >= gd.powerUpTimer)
	{
		gd.isPowerUpSpawned = true;

		Vector2 powerUpPosition = { static_cast<float>(GetRandomValue(gd.player1.hitBox.position.x + 10, gd.player2.hitBox.position.x - 10)), static_cast<float>(GetRandomValue(0, GetScreenHeight() - gd.powerUpObject.size)) };
		SetPowerUp(gd.powerUpObject, powerUpPosition);
	}

	if (GetTime() >= gd.activeModifierTimer)
	{
		if (gd.player1.isModified)
			ResetPlayer(gd.player1);
		if (gd.player2.isModified)
			ResetPlayer(gd.player2);
	}
	if (gd.playerOneScore >= 7 || gd.playerTwoScore >= 7)
	{
		if (gd.playerOneScore >= 7)
			gd.player1HasWon = true;

		gd.isPaused = true;
		gd.isGameOver = true;
	}
	BallUpdate(gd.ball);
	CollisionUpdate();
}
void GameDraw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	TableDraw();
	PaddleDraw(gd.player1);
	PaddleDraw(gd.player2);
	BallDraw(gd.ball);
	if (gd.isPowerUpSpawned)
		PowerUpDraw(gd.powerUpObject);
	EndDrawing();
}

void ResetGameStats()
{
	gd.playerOneScore = 0;
	gd.playerTwoScore = 0;
	gd.isGameOver = false;
	gd.player1HasWon = false;
	gd.isPaused = true;
	gd.areRulesShown = true;
	gd.isPowerUpSpawned = false;
	gd.powerUpTimer = GetTime() + gd.powerUpSpawnRate;
	ResetBall(gd.ball);
	ResetPlayer(gd.player1);
	ResetPlayer(gd.player2);
}

void PauseUpdate(Scenes& scene)
{
	if (gd.areRulesShown)
	{
		if (GetKeyPressed())
		{
			gd.isPaused = false;
			gd.areRulesShown = false;
		}
	}
	else if (gd.isGameOver)
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			gd.isGameOver = false;
			gd.player1HasWon = false;
			scene = Scenes::Menu;
		}
		else if (IsKeyPressed(KEY_SPACE))
		{
			gd.justRestarted = true;
		}
	}
	else
	{
		if (IsKeyPressed(KEY_ESCAPE))
			gd.isPaused = false;

		if (IsKeyPressed(KEY_SPACE))
			scene = Scenes::Menu;
	}
}
void PauseDraw()
{
	BeginDrawing();
	Color panelColor = BLACK;
	if (!gd.areRulesShown)
		panelColor = ColorAlpha(panelColor, 0.010f);
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), panelColor);

	if (gd.areRulesShown)
	{
		const char* rulesTitle = "Rules";
		int titleSize = 120;
		int rulesSize = 40;
		const char* winConditionText = "First who reaches 7 points wins the game";
		const char* powerUpsText = "Pick PowerUps to get an advantage on your opponent";
		const char* pressAnyKeyText = "Press any key to start the game";
		DrawText(rulesTitle, GetScreenWidth() / 2 - MeasureText(rulesTitle, titleSize) / 2, 20, titleSize, WHITE);
		DrawText(pressAnyKeyText, GetScreenWidth() / 2 - MeasureText(pressAnyKeyText, rulesSize) / 2, GetScreenHeight() - 80, rulesSize, WHITE);

		if (gd.isSinglePlayer)
			DrawText(winConditionText, GetScreenWidth() / 2 - MeasureText(winConditionText, rulesSize) / 2, GetScreenHeight() / 2, rulesSize, WHITE);
		else
		{
			DrawText(winConditionText, GetScreenWidth() / 2 - MeasureText(winConditionText, rulesSize) / 2, GetScreenHeight() / 3, rulesSize, WHITE);
			DrawText(powerUpsText, GetScreenWidth() / 2 - MeasureText(powerUpsText, rulesSize) / 2, GetScreenHeight() / 3 + 120, rulesSize, WHITE);
		}
	}
	else if (gd.isGameOver)
	{
		const char* gameOver = "Game Over";
		int gameOverSize = 120;
		const char* winnerText = " ";
		int winnerSize = 80;

		const char* pressKeyText = "Press Escape to go to main menu, Space to restart the game";
		int pressKeySize = 40;

		if (gd.player1HasWon)
			winnerText = "Player 1 Wins!";
		else if (!gd.player1HasWon && !gd.isSinglePlayer)
			winnerText = "Player 2 Wins!";
		else if (!gd.player1HasWon && gd.isSinglePlayer)
			winnerText = "You Lost to a Bot :(";

		DrawText(gameOver, GetScreenWidth() / 2 - MeasureText(gameOver, gameOverSize) / 2, 20, gameOverSize, WHITE);
		DrawText(winnerText, GetScreenWidth() / 2 - MeasureText(winnerText, winnerSize) / 2, GetScreenHeight() / 2, winnerSize, WHITE);
		DrawText(pressKeyText, GetScreenWidth() / 2 - MeasureText(pressKeyText, pressKeySize) / 2, GetScreenHeight() - 50, pressKeySize, WHITE);

	}
	else
	{
		const char* pauseTitle = "Game is Paused";
		int titleSize = 120;

		const char* backToMenuText = "Press Space to go to Main Menu";
		int backToMenuSize = 60;
		DrawText(pauseTitle, GetScreenWidth() / 2 - MeasureText(pauseTitle, titleSize) / 2, 20, titleSize, WHITE);
		DrawText(backToMenuText, GetScreenWidth() / 2 - MeasureText(backToMenuText, backToMenuSize) / 2, GetScreenHeight() - 80, backToMenuSize, WHITE);
	}

	EndDrawing();
}

void CollisionUpdate()
{
	BallBorderCollision();
	BallPaddleCollision(gd.ball, gd.player1);
	BallPaddleCollision(gd.ball, gd.player2);
	if (gd.isPowerUpSpawned)
		BallPowerUpCollision();
}
void BallBorderCollision()
{
	if (gd.ball.position.x < 0)
	{
		gd.ball.position = gd.ball.startPosition;
		gd.ball.speed = gd.ball.baseSpeed;
		gd.playerTwoScore++;
		RandomServe(gd.ball, false);
		ResetBall(gd.ball);
		ResetPlayer(gd.player1);
		ResetPlayer(gd.player2);
	}
	else if (gd.ball.position.x + gd.ball.size > GetScreenWidth())
	{
		gd.ball.position = gd.ball.startPosition;
		gd.ball.speed = gd.ball.baseSpeed;
		gd.playerOneScore++;
		RandomServe(gd.ball, false);
		ResetBall(gd.ball);
		ResetPlayer(gd.player1);
		ResetPlayer(gd.player2);
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
		ball.lastPaddleHitted = player;
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

void BallPowerUpCollision()
{
	if (gd.ball.position.x + gd.ball.size >= gd.powerUpObject.position.x
		&& gd.ball.position.x <= gd.powerUpObject.position.x + gd.powerUpObject.size
		&& gd.ball.position.y + gd.ball.size >= gd.powerUpObject.position.y
		&& gd.ball.position.y <= gd.powerUpObject.position.y + gd.powerUpObject.size)
	{
		PickPowerUp();
	}
}
void PickPowerUp()
{
	gd.powerUpTimer = GetTime() + gd.powerUpSpawnRate;
	gd.isPowerUpSpawned = false;
	switch (gd.powerUpObject.type)
	{
	case PowerUpType::SpeedBoost:
		if (gd.ball.lastPaddleHitted.isPlayer1)
			SpeedBoost(gd.player1, gd.activeModifierTimer);
		else
			SpeedBoost(gd.player2, gd.activeModifierTimer);
		break;
	case PowerUpType::FireBall:
		FireBall(gd.ball);
		break;
	case PowerUpType::SlowDown:
		if (gd.ball.lastPaddleHitted.isPlayer1)
			SlowDown(gd.player2, gd.activeModifierTimer);
		else
			SlowDown(gd.player1, gd.activeModifierTimer);
		break;
	default:
		break;
	}
}

void TableDraw()
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
