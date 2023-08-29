#include "Menu.h"

void MenuStart(GameData& gd, MenuData& md);
void MenuUpdate(GameData& gd, MenuData& md);
void MenuDraw(GameData& gd, MenuData& md);

void Menu(GameData& gd)
{
	static MenuData menuData;
	if (gd.enteredNewScene)
		MenuStart(gd, menuData);
	
	MenuUpdate(gd, menuData);
	MenuDraw(gd, menuData);
}

void MenuStart(GameData& gd, MenuData& menuData)
{
	menuData.singlePlayerButton = { {15, static_cast<float>(GetScreenHeight()) / 4}, 50, 250 };
}
void MenuUpdate(GameData& gd, MenuData& menuData)
{

}
void MenuDraw(GameData& gd, MenuData& menuData)
{
	BeginDrawing();

	DrawRectangle(menuData.singlePlayerButton.position.x, menuData.singlePlayerButton.position.y, menuData.singlePlayerButton.width, menuData.singlePlayerButton.height, WHITE);

	EndDrawing();
}