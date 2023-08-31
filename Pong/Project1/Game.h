#pragma once
#include "Ball.h"
#include "Player.h"
#include "Cpu.h"

enum class Scenes
{
	Menu,
	Game,
	Options,
	GameOver,
	GameQuit
};

struct GameData
{
	Scenes scene = Scenes::Menu;
	Scenes prevScene;
	bool enteredNewScene;

	bool areRulesShown = false;
	bool isPaused = false;
	Paddle player1{};
	int playerOneScore = 0;
	int playerTwoScore = 0;
	bool isSinglePlayer = false;
	bool player1HasWon = false;
	Paddle player2{};
	Ball ball{};
};

void Game(GameData& gd);
