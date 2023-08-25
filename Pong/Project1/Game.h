#pragma once
#include "Ball.h"
#include "Player.h"
using namespace std;

struct GameData
{
	Paddle player1{};
	int playerOneScore = 0;
	int playerTwoScore = 0;
	Paddle player2{};
	Ball ball{};
};
void RunGame();