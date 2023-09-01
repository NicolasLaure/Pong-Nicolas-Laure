#include "ProgramLoop.h"
#include "Menu.h"
#include <iostream>
#include "Game.h"

using namespace game; 
using namespace std;

void Initialize(GameData& gd);
void GameLoop(GameData& gd, MenuData& menuData);

void RunGame()
{
	GameData gd;
	MenuData menuData;
	Initialize(gd);
	GameLoop(gd, menuData);
	CloseWindow();
}

void Initialize(GameData& gd)
{
	InitWindow(1280, 720, "Prototipo");
	SetExitKey(NULL);
	SetRandomSeed(time(0));
}

void GameLoop(GameData& gd, MenuData& menuData)
{
	do
	{
		if (!gd.justRestarted)
			gd.enteredNewScene = gd.scene != gd.prevScene;
		else
			gd.justRestarted = false;

		gd.prevScene = gd.scene;

		switch (gd.scene)
		{
		case Scenes::GameQuit:
			break;
		case Scenes::Menu:
			Menu(gd, menuData);
			break;
		case Scenes::Game:
			Game(gd);
			break;
		default:
			break;
		}
	} while (gd.scene != Scenes::GameQuit && !WindowShouldClose());
}