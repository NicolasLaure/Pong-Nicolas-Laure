#include "ProgramLoop.h"
#include "Menu.h"
#include "Game.h"

using namespace game;
using namespace std;

static SceneManager sceneManager;

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
	SetRandomSeed(time(nullptr));
}

void GameLoop()
{
	sceneManager.scene = Scenes::Menu;
	sceneManager.prevScene = Scenes::GameQuit;
	sceneManager.enteredNewScene = false;
	sceneManager.justRestarted = false;

	sceneManager.isSinglePlayer = false;
	sceneManager.isPaused = false;
	do
	{
		if (!sceneManager.justRestarted)
			sceneManager.enteredNewScene = sceneManager.scene != sceneManager.prevScene;
		else
		{
			sceneManager.enteredNewScene = true;
			sceneManager.justRestarted = false;
		}

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
			GameLoop(sceneManager.enteredNewScene, sceneManager.scene, sceneManager.justRestarted);
			break;
		default:
			break;
		}
	} while (sceneManager.scene != Scenes::GameQuit && !WindowShouldClose());
}