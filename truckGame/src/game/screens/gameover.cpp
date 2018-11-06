#include "gameover.h"

#include "Setup/game.h"
#include "Screens/gameplay.h"
#include "Setup/player.h"
#include "Screens/settings.h"
#include "Screens/menu.h"

using namespace Juego;
using namespace Gameplay_Section;
using namespace Menu_Section;

namespace Juego
{

	static const int maxButtons = 2;

	static Buttons buttons[maxButtons];
	static int buttonDistance = 0;
	static int buttonSelect = 0;
	static Color optionColor = RED;

	static bool isButtonSoundPlaying = false;
	static int buttonSelectSaveNumber = 0;

	namespace GameOver_Section
	{
		static void createGameOverButtons()
		{
			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 2.5f;
				buttons[i].position.y = (float)screenHeight / 3.0f + buttonDistance;
				buttons[i].width = (float)screenWidth / 5.0f;

				if (resolutionNormal) buttons[i].height = (float)screenHeight / 12.0f;
				else if (resolutionSmall) buttons[i].height = (float)screenHeight / 14.0f;

				buttons[i].selected = false;
				buttons[i].defaultColor = GREEN;
				buttons[i].messageColor = BLANK;

				if (resolutionNormal && !(resolutionBig)) buttonDistance = buttonDistance + 100;
				else if (resolutionSmall) buttonDistance = buttonDistance + 60;
				else if (resolutionBig && resolutionNormal) buttonDistance = buttonDistance + 125;
			}
		}

		void InitGameOverScreen()
		{			

			#ifdef AUDIO
			ship_explode01 = LoadSound("res/assets/sounds/explosionlong.wav");
			SetSoundVolume(ship_explode01, soundVolume);

			if(!player.isAlive)PlaySound(ship_explode01);
			
			SetSoundVolume(button_select01, soundVolume);
			SetSoundVolume(button_navigate01, soundVolume);
			#endif

			ShowCursor();
			createGameOverButtons();
			isScreenFinished = false;
		}

		static void GameOverInput()
		{

			for (int i = 0; i < maxButtons; i++)
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttons[i].selected || IsKeyPressed(KEY_ENTER) && buttons[i].selected)
				{
					//PlaySound(button_select01);
					switch (i)
					{
					case 0:
						buttonOption = buttonRestart;
						break;
					case 1:
						buttonOption = buttonQuitToMenu;
						break;
					}
					buttons[i].selected = false;
					isScreenFinished = true;
				}
			}
		}

		void UpdateGameOverScreen()
		{
			GameOverInput(); 
			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };
			

			for (int i = 0; i < maxButtons; i++)
			{
				if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height }) || buttonSelect == i)
				{
					buttonSelect = i;
					buttons[i].defaultColor = GREEN;
					buttons[i].selected = true;
				}
				else
				{
					buttons[i].defaultColor = DARKGREEN;
					buttons[i].selected = false;
					buttonSelect = -1;
				}

				if (buttonSelect != buttonSelectSaveNumber && buttonSelect != -1)
				{
					isButtonSoundPlaying = false;
				}

				if (buttonSelect == i)
				{
					if (!(isButtonSoundPlaying))
					{
						//PlaySound(button_navigate01);
						isButtonSoundPlaying = true;
						buttonSelectSaveNumber = i;
					}
				}
			}
		}

		void DrawGameOver()
		{
			if (player.isAlive) DrawBackground();
			else DrawBackgroundBroken();
			

			for (int i = 0; i < maxButtons; i++)
			{
				DrawRectangleLines(buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height, buttons[i].defaultColor);
			}

			DrawTextEx(sideFont, "RESTART", { buttons[0].position.x + 10, buttons[0].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[0].defaultColor);
			DrawTextEx(sideFont, "MENU", { buttons[1].position.x + 10, buttons[1].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[1].defaultColor);

			//if (targetsLeft == 0 && player.isAlive)
			//{
			//	DrawTextEx(mainFont, "MISSION SUCCESSFUL", { buttons[0].position.x - screenWidth/5.0f, buttons[0].position.y - 60 }, defaultFontSize / 1.2, 1.0f, GOLD);
			//}
			//else
			//{
			//	DrawTextEx(mainFont, "MISSION FAILED", { buttons[0].position.x - screenWidth / 10.0f, buttons[0].position.y - 60 }, defaultFontSize / 1.2, 1.0f, GREEN);
			//}
			
		}

		bool FinishGameOverScreen()
		{
			buttonDistance = 0;
			return isScreenFinished;
		}

		void DeInitGameOverResources()
		{
			#ifdef AUDIO
			StopSound(ship_explode01);
			UnloadSound(ship_explode01);
			#endif
		}
	}
}