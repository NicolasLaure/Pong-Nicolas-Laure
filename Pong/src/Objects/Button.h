#pragma once
#include "GameManagement/Utilities.h"
#include "GameManagement/Scenes.h"

struct Button
{
	Rect buttonRect;
	Scenes sceneTo;
	bool isSinglePlayer;
	const char* text;
	int fontSize = 70;
	Color textColor = WHITE;
	Color currentTextColor = WHITE;


	float textHeightSpacerMultiplier = 1.6f;
	float textPositionX = 15;
};