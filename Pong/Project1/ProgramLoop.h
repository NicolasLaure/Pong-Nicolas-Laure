#pragma once
#include "Scenes.h"
#include <iostream>

struct SceneManager
{
	Scenes scene;
	Scenes prevScene;
	bool enteredNewScene;

	bool isSinglePlayer;
	bool isPaused = false;
};

void RunGame();