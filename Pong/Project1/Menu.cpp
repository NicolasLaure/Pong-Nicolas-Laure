#include "Menu.h"

void MenuStart(GameData& gd, MenuData& md);
void MenuUpdate(GameData& gd, MenuData& md);
void MenuDraw(GameData& gd, MenuData& md);

void Menu(GameData& gd, MenuData& menuData)
{
	if (gd.enteredNewScene)
		MenuStart(gd, menuData);

	MenuUpdate(gd, menuData);
	MenuDraw(gd, menuData);
}

void MenuStart(GameData& gd, MenuData& menuData)
{
	Vector2 textSize;
	for (int i = 0; i < menuData.buttonsQty; i++)
	{
		textSize = MeasureTextEx(GetFontDefault(), menuData.buttons[i].text, menuData.buttons[i].fontSize, menuData.buttons[i].fontSize * 0.1f);
		menuData.buttons[i].buttonRect = { {15, static_cast<float>(GetScreenHeight()) / 3 + i * menuData.buttons[i].fontSize * 1.5f}, textSize.y, textSize.x };
	}
}
void MenuUpdate(GameData& gd, MenuData& menuData)
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
				gd.scene = button.sceneTo;
				gd.isSinglePlayer = button.isSinglePlayer;
			}
		}
		else
			button.currentTextColor = button.textColor;

	}
}
void MenuDraw(GameData& gd, MenuData& menuData)
{
	BeginDrawing();

	ClearBackground(BLACK);
	DrawText(menuData.title, GetScreenWidth() / 2 - MeasureText(menuData.title, menuData.titleSize) / 2, 20, menuData.titleSize, WHITE);
	DrawText(menuData.credits, GetScreenWidth() - MeasureText(menuData.credits, menuData.creditsSize) - 20, GetScreenHeight() - menuData.creditsSize - 20, menuData.creditsSize, WHITE);

	for (Button& button : menuData.buttons)
	{
		DrawRectangle(button.buttonRect.position.x, button.buttonRect.position.y, button.buttonRect.width, button.buttonRect.height, BLACK);
		DrawText(button.text, button.buttonRect.position.x, button.buttonRect.position.y, button.fontSize, button.currentTextColor);
	}
	EndDrawing();
}