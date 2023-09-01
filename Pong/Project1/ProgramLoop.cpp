#include "ProgramLoop.h"
#include "Menu.h"
#include <iostream>
#include "Game.h"

using namespace game;
using namespace std;

void Initialize();
void GameLoop();

void RunGame()
{
	Initialize();
	GameLoop();
	CloseWindow();
}

void Initialize()
{
	InitWindow(1280, 720, "Prototipo");
	SetExitKey(NULL);
	SetRandomSeed(time(0));
}

void GameLoop()
{
	SceneManager sceneManager;
	sceneManager.scene = Scenes::Menu;
	do
	{
		sceneManager.enteredNewScene = sceneManager.scene != sceneManager.prevScene;

		sceneManager.prevScene = sceneManager.scene;

		switch (sceneManager.scene)
		{
		case Scenes::GameQuit:
			break;
		case Scenes::Menu:
			if (sceneManager.enteredNewScene)
				MenuStart();

			MenuUpdate(sceneManager.scene, sceneManager.isSinglePlayer);
			MenuDraw();
			break;
		case Scenes::Game:
			GameLoop(sceneManager.enteredNewScene, sceneManager.scene);
			break;
		default:
			break;
		}
	} while (sceneManager.scene != Scenes::GameQuit && !WindowShouldClose());
}