#include "GameManagement/Menu.h"

static MenuData menuData;

void MenuStart()
{
	menuData.title = "Elemental Pong";
	Vector2 textSize;

	
	for (int i = 0; i < menuData.buttonsQty; i++)
	{
		textSize = MeasureTextEx(GetFontDefault(), menuData.buttons[i].text, menuData.buttons[i].fontSize, menuData.buttons[i].fontSize * 0.1f);
		menuData.buttons[i].buttonRect = { {menuData.buttons[i].textPositionX, static_cast<float>(GetScreenHeight()) / 3 + i * menuData.buttons[i].fontSize * menuData.buttons[i].textHeightSpacerMultiplier}, textSize.y, textSize.x };
	}
}
void MenuUpdate(Scenes& scene, bool& isSinglePlayer)
{
	Vector2 mousePos = GetMousePosition();
	for (Button& button : menuData.buttons)
	{
		if (mousePos.x > button.buttonRect.position.x
			&& mousePos.x <  button.buttonRect.position.x + button.buttonRect.width
			&& mousePos.y > button.buttonRect.position.y
			&& mousePos.y < button.buttonRect.position.y + button.buttonRect.height)
		{
			button.currentTextColor = GRAY;
			if (IsMouseButtonDown(0))
			{
				button.currentTextColor = DARKGRAY;
			}
			if (IsMouseButtonReleased(0))
			{
				scene = button.sceneTo;
				isSinglePlayer = button.isSinglePlayer;
			}
		}
		else
			button.currentTextColor = button.textColor;

	}
}
void MenuDraw()
{
	BeginDrawing();

	int windowLimitSpacing = 20;
	ClearBackground(BLACK);
	DrawText(menuData.title, GetScreenWidth() / 2 - MeasureText(menuData.title, menuData.titleSize) / 2, windowLimitSpacing, menuData.titleSize, WHITE);
	DrawText(menuData.credits, GetScreenWidth() - MeasureText(menuData.credits, menuData.creditsSize) - windowLimitSpacing, GetScreenHeight() - menuData.creditsSize - windowLimitSpacing, menuData.creditsSize, WHITE);

	for (Button& button : menuData.buttons)
	{
		DrawRectangle(button.buttonRect.position.x, button.buttonRect.position.y, button.buttonRect.width, button.buttonRect.height, BLACK);
		DrawText(button.text, button.buttonRect.position.x, button.buttonRect.position.y, button.fontSize, button.currentTextColor);
	}
	EndDrawing();
}