#pragma once
#include "Button.h"
#include "Scenes.h"

void MenuStart();
void MenuUpdate(Scenes& scene, bool isSinglePlayer);
void MenuDraw();

static struct MenuData
{
	const char* title = "Elemental Pong";
	int titleSize = 120;

	const char* credits = "Created By Nico Laure";
	int creditsSize = 30;

	static const int buttonsQty = 3;
	Button buttons[buttonsQty] = {
		{{0,0}, Scenes::Game, true, "Single Player"},
		{{0,0}, Scenes::Game, false, "Two Player"},
		{{0,0}, Scenes::GameQuit, false,"Exit Game"}
	};
};