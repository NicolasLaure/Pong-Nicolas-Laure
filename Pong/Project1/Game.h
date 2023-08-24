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

void Initialize(GameData& gd);

void GameUpdate(GameData& gd);
void GameDraw(GameData gd);
void TableDraw(GameData gd);
void ScoreDraw(int score, Vector2 position);

void CollisionUpdate(GameData& gd);
bool BallPaddleCollision(Box ballHitBox, Box paddleBox);
