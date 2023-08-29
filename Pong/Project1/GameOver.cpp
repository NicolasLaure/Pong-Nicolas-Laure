#include "GameOver.h"

void GameOverStart(GameData& gd);
void GameOverUpdate(GameData& gd);
void GameOverDraw(GameData& gd);

void GameOver(GameData& gd)
{
	if (gd.enteredNewScene)
		GameOverStart(gd);

	GameOverUpdate(gd);
	GameOverDraw(gd);
}
void GameOverStart(GameData& gd)
{

}
void GameOverUpdate(GameData& gd)
{
	if (GetKeyPressed())
		gd.scene = Scenes::Menu;
}
void GameOverDraw(GameData& gd)
{

}