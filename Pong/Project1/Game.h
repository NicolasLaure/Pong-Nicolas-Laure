#pragma once
#include "Ball.h"
#include "Player.h"


enum class Scenes
{
	Menu,
	Game,
	GameOver,
	GameQuit
};

struct GameData
{

	Scenes scene = Scenes::Menu;
	Scenes prevScene;
	bool enteredNewScene;

	Paddle player1{};
	int playerOneScore = 0;
	int playerTwoScore = 0;
	bool isSinglePlayer = false;
	bool player1HasWon = false;
	Paddle player2{};
	Ball ball{};
};

void Game(GameData& gd);
