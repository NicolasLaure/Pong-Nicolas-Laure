#pragma once
#include "Game.h"

struct MenuData
{
	Rect singlePlayerButton;
	Rect twoPlayerButton;
	Rect quitButton;
};

void Menu(GameData& gd);
