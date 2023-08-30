#pragma once
#include "Game.h"

struct Button
{
	Rect buttonRect;
	Scenes sceneTo;
	bool isSinglePlayer;
	const char* text;
	int fontSize = 70;
	Color textColor = WHITE;
	Color currentTextColor = WHITE;
};

struct MenuData
{

	const char* title = "Elemental Pong";
	int titleSize = 120;

	const char* credits = "Created By Nico Laure";
	int creditsSize = 30;

	static const int buttonsQty = 4;
	Button buttons[buttonsQty] = {
		{{0,0}, Scenes::Game, true, "Single Player"},
		{{0,0}, Scenes::Game, false, "Two Player"},
		{{0,0}, Scenes::Options, false, "Options"},
		{{0,0}, Scenes::GameQuit, false,"Exit Game"}
	};
};

void Menu(GameData& gd);
