#pragma once
#include "Objects/Ball.h"
#include "Objects/Player.h"
#include "Objects/Cpu.h"
#include "Objects/PowerUps.h"
#include "GameManagement/Scenes.h"

namespace game
{
	struct GameData
	{
		bool areRulesShown = false;
		bool isPaused = false;
		Paddle player1{};
		int playerOneScore = 0;
		int playerTwoScore = 0;
		int pointsToWin = 7;
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

	void GameLoop(bool enteredNewScene, Scenes& scene, bool isSinglePlayer);
}