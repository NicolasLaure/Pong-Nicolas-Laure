#include "ProgramLoop.h"
#include "GameOver.h"
#include "Menu.h"
#include <iostream>

using namespace std;

void Initialize(GameData& gd);
void GameLoop(GameData& gd);

void RunGame()
{
	GameData gd;
	Initialize(gd);
	GameLoop(gd);
	CloseWindow();
}

void Initialize(GameData& gd)
{
	InitWindow(1280, 720, "Prototipo");
	SetExitKey(NULL);
	SetRandomSeed(time(0));
}

void GameLoop(GameData& gd)
{
	do
	{
		gd.enteredNewScene = gd.scene != gd.prevScene;
		gd.prevScene = gd.scene;

		switch (gd.scene)
		{
		case Scenes::GameQuit:
			break;
		case Scenes::Menu:
			Menu(gd);
			break;
		case Scenes::Game:
			Game(gd);
			break;
		case Scenes::GameOver:
			GameOver(gd);
			break;
		default:
			break;
		}
	} while (gd.scene != Scenes::GameQuit && !WindowShouldClose());
}