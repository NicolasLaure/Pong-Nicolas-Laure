#pragma once
#include "Utilities.h"
#include "Scenes.h"

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