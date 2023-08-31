#include "Game.h"
#include <cmath>

void Game(GameData& gd);
void GameStart(GameData& gd);
void GameUpdate(GameData& gd);
void GameDraw(GameData gd);

void PauseUpdate(GameData& gd);
void PauseDraw(GameData& gd);

void TableDraw(GameData gd);
void ScoreDraw(int score, Vector2 position);

void CollisionUpdate(GameData& gd);
void BallBorderCollision(GameData& gd);
void BallPaddleCollision(Ball& ball, Paddle& player);

void Game(GameData& gd)
{
	if (gd.enteredNewScene)
		GameStart(gd);

	if (!gd.isPaused)
	{
		GameUpdate(gd);
		GameDraw(gd);
	}
	else
	{
		PauseUpdate(gd);
		PauseDraw(gd);
	}
}
void GameStart(GameData& gd)
{
	gd.playerOneScore = 0;
	gd.playerTwoScore = 0;
	gd.player1HasWon = false;
	gd.isPaused = true;
	gd.areRulesShown = true;

	gd.powerUpTimer = GetTime() + gd.powerUpSpawnRate;

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
	else
		CpuUpdate(gd.player2, gd.ball);

	if (IsKeyPressed(KEY_ESCAPE))
	{
		if (!gd.isPaused)
			gd.isPaused = true;
		else
			gd.isPaused = false;
	}

	if (!gd.isPowerUpSpawned && gd.powerUpTimer)
	{
		gd.isPowerUpSpawned = true;

		gd.powerUpObject.position;
		//
	}

	if (GetTime() >= gd.activeModifierTimer)
	{
		if (gd.isPlayer1Modified)
			ResetPlayer(gd.player1);
		if (gd.isPlayer2Modified)
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
	CollisionUpdate(gd);
}
void GameDraw(GameData gd)
{
	BeginDrawing();
	ClearBackground(BLACK);

	TableDraw(gd);
	PaddleDraw(gd.player1);
	PaddleDraw(gd.player2);
	BallDraw(gd.ball);

	EndDrawing();
}

void PauseUpdate(GameData& gd)
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
			gd.scene = Scenes::Menu;
		}
		else if (IsKeyPressed(KEY_SPACE))
		{
			gd.isGameOver = false;
			gd.player1HasWon = false;
			gd.enteredNewScene = true;
			gd.justRestarted = true;
		}
	}
	else
	{
		if (IsKeyPressed(KEY_ESCAPE))
			gd.isPaused = false;

		if (IsKeyPressed(KEY_SPACE))
			gd.scene = Scenes::Menu;
	}
}
void PauseDraw(GameData& gd)
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
		RandomServe(gd.ball, false);
	}
	else if (gd.ball.position.x + gd.ball.size > GetScreenWidth())
	{
		gd.ball.position = gd.ball.startPosition;
		gd.ball.speed = gd.ball.baseSpeed;
		gd.playerOneScore++;
		RandomServe(gd.ball, false);
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