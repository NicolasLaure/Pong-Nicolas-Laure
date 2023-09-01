#pragma once
#include "Scenes.h"

struct SceneManager
{
	Scenes scene;
	Scenes prevScene;
	bool enteredNewScene;

	bool isSinglePlayer;
	bool isPaused = false;
};

void RunGame();