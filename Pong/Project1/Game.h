#pragma once
#include "Ball.h"
#include "Player.h"
#include "Cpu.h"
#include "PowerUps.h"
#include "Scenes.h"

namespace game
{
	/*enum class Scenes
	{
		Menu,
		Game,
		Options,
		GameQuit
	};*/

	struct GameData
	{
		/*Scenes scene = Scenes::Menu;
		Scenes prevScene;
		bool enteredNewScene;*/

		bool areRulesShown = false;
		bool isPaused = false;
		Paddle player1{};
		int playerOneScore = 0;
		int playerTwoScore = 0;
		bool isSinglePlayer = false;
		bool player1HasWon = false;
		Paddle player2{};
		Ball ball{};

		bool isGameOver = false;
		bool justRestarted = false;

		PowerUp powerUpObject;
		float powerUpTimer{};
		float powerUpSpawnRate = 8;
		bool isPowerUpSpawned = false;

		float activeModifierTimer;
	};

	void GameLoop(bool enteredNewScene, Scenes& scene);
}