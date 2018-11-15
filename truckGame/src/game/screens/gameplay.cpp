#include "gameplay.h"

#include "setup/game.h"
#include "setup/player.h"
#include "screens/settings.h"
#include "screens/menu.h"
#include "setup/level.h"

namespace Juego
{
	bool gameON = true;

	int playerKeys[MAX];

	static const int maxButtons = 3;
	static Buttons buttons[maxButtons];
	static Buttons pauseButton;
	static int buttonDistance = 0;
	static int buttonSelect = 0;
	static Color optionColor = RED;

	static bool gamePaused = false;
	
	static bool timerON = true;

	static Rectangle pauseBoxRec;

	static bool isButtonSoundPlaying = false;
	static int buttonSelectSaveNumber = 0;

	static int garbagePoints = 0;

	namespace Gameplay_Section
	{
		static void createPauseButtons()
		{

			for (int i = 0; i < maxButtons; i++)
			{
				buttons[i].position.x = (float)screenWidth / 2.5f; // 2.5F
				buttons[i].position.y = (float)screenHeight / 3.0f + buttonDistance;
				buttons[i].width = (float)screenWidth / 5.0f;

				if (resolutionNormal) buttons[i].height = (float)screenHeight / 12.0f;
				else if (resolutionSmall) buttons[i].height = (float)screenHeight / 14.0f;

				buttons[i].selected = false;
				buttons[i].defaultColor = GOLD;
				buttons[i].messageColor = BLANK;

				if (resolutionNormal && !(resolutionBig)) buttonDistance = buttonDistance + 100;
				else if (resolutionSmall) buttonDistance = buttonDistance + 60;
				else if (resolutionBig && resolutionNormal) buttonDistance = buttonDistance + 125;
			}

			pauseButton.position.x = (float)screenWidth / 1.4f;//1.4F
			pauseButton.position.y = (float)screenHeight / 210.0f; // 14.0F
			pauseButton.width = (float)screenWidth / 22.0f;//18


			pauseBoxRec = { buttons[0].position.x - (screenWidth / 50), buttons[0].position.y - (screenHeight / 30), (float)screenWidth / 4.2f, (float)screenHeight / 2.5f };
			pauseButton.height = (float)screenHeight / 18.0f;//12

			pauseButton.selected = false;
			pauseButton.defaultColor = DARKGREEN;
			pauseButton.messageColor = BLANK;
		}

		void InitGameplayVariables()
		{
			timerON = true;
			createPauseButtons();
			createLevelBackground();
			createLevelObstacles();
			createPlayer();
		}

		void InitGameplayParallax()
		{

		}

		void InitGameplayScreen()
		{
			currentLevel = 0;

			if (resolutionNormal)
			{
				//shipImage = LoadImage("res/assets/textures/player_ship01v2.png");
				//ImageResize(&shipImage, 300, 70);// 150 70
				//ship = LoadTextureFromImage(shipImage);

				//enemyShipImage = LoadImage("res/assets/textures/enemy01.png");
				//ImageResize(&enemyShipImage, 180, 70);
				//enemyShip = LoadTextureFromImage(enemyShipImage);

				//pauseMenuImage = LoadImage("res/assets/textures/pausemenu.png");
				//ImageResize(&pauseMenuImage, pauseBoxRec.width, pauseBoxRec.height);
				//pauseMenu = LoadTextureFromImage(pauseMenuImage);

				//UnloadImage(pauseMenuImage);
				//UnloadImage(shipImage);
				//UnloadImage(enemyShipImage);

			}
			else if (resolutionSmall)
			{
				//shipImage = LoadImage("res/assets/textures/player_ship01v2.png");
				//ImageResize(&shipImage, 300/1.5f, 70/1.5f);// 150 70
				//ship = LoadTextureFromImage(shipImage);

				//enemyShipImage = LoadImage("res/assets/textures/enemy01.png");
				//ImageResize(&enemyShipImage, 180 / 1.5f, 70 / 1.5f);
				//enemyShip = LoadTextureFromImage(enemyShipImage);

				//pauseMenuImage = LoadImage("res/assets/textures/pausemenu.png");
				//ImageResize(&pauseMenuImage, pauseBoxRec.width, pauseBoxRec.height);
				//pauseMenu = LoadTextureFromImage(pauseMenuImage);

				//UnloadImage(pauseMenuImage);
				//UnloadImage(shipImage);
				//UnloadImage(enemyShipImage);
			}

			#ifdef AUDIO
			ship_shoot01 = LoadSound("res/assets/sounds/shoot01.wav");
			SetSoundVolume(ship_shoot01, soundVolume);

			enemy_explode01 = LoadSound("res/assets/sounds/explosion1.wav");
			SetSoundVolume(enemy_explode01, soundVolume);

			SetSoundVolume(button_select01, soundVolume);
			SetSoundVolume(button_navigate01, soundVolume);
			#endif
			isScreenFinished = false;
		}

		static void GameplayInput()
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && pauseButton.selected)
			{
				//PlaySound(button_select01);
				gamePaused = true;
				gameON = false;
			}

			// Player Input
			if (gameON)
			{
				timerON = true;
				playerInput();
			}
			else ShowCursor();

			if (!gamePaused)
			{
				if (IsKeyPressed(KEY_ESCAPE))
				{
					//PlaySound(button_select01);
					//crosshairColor = BLANK;
					gamePaused = true;
					gameON = false;
				}
			}
			else
			{

				for (int i = 0; i < maxButtons; i++)
				{
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && buttons[i].selected || IsKeyPressed(KEY_ENTER) && buttons[i].selected)
					{
						//PlaySound(button_select01);
						switch (i)
						{
						case 0:
							gamePaused = false;
							timerON = true;
							gameON = true;
							break;
						case 1:
							RestartPhase();
							break;
						case 2:
							buttonOption = buttonQuitToMenu;
							isScreenFinished = true;
							break;
						}
						buttons[i].selected = false;
					}
				}

				if (IsKeyPressed(KEY_ESCAPE))
				{
					//PlaySound(button_select01);
					gamePaused = false;
					timerON = true;
					gameON = true;
				}
			}
		}

		void UpdateGameplayScreen()
		{	
			player.inputActive = false;

			mouse.position = { (float)GetMouseX(),(float)GetMouseY() };
			GameplayInput();

			if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { pauseButton.position.x, pauseButton.position.y, pauseButton.width, pauseButton.height }))
			{
				pauseButton.defaultColor = RED;
				pauseButton.selected = true;
			}
			else
			{
				pauseButton.defaultColor = DARKGREEN;
				pauseButton.selected = false;
			} 

			if (gameON)
			{		
				playerUpdate();
				for (int i = 0; i < maxGarbageBoxes; i++)
				{
					if (garbageBox[i].isOnPlayer)
					{
						garbageBox[i].pos.x = playerhitbox.position.x + (playerhitbox.size.x / 2) - (garbageBox[i].size.x / 2);
						garbageBox[i].pos.y = playerhitbox.position.y + (playerhitbox.size.y / 2) - (garbageBox[i].size.y / 2);
					}
					else if (!(garbageBox[i].isOnPlayer))
					{
						//garbageAccelerationUp = playerAccelerationDown;
						garbageBox[i].pos.x += garbageBox[i].AccelerationRight * GetFrameTime();
						garbageBox[i].pos.x -= garbageBox[i].AccelerationLeft * GetFrameTime();
						garbageBox[i].pos.y += garbageBox[i].AccelerationDown * GetFrameTime();
						garbageBox[i].pos.y -= garbageBox[i].AccelerationUp * GetFrameTime();
					}

					if (CheckCollisionRecs({ garbageBox[i].pos.x,garbageBox[i].pos.y,garbageBox[i].size.x,garbageBox[i].size.y }, { obstacles[obDumpster].pos.x ,obstacles[obDumpster].pos.y,obstacles[obDumpster].size.x,obstacles[obDumpster].size.y }) && garbageBox[i].isAlive)
					{
						garbageBox[i].isAlive = false;
						garbagePoints++;	
					}

					if (!(garbageBox[i].isAlive))
					{
						garbageBox[i].size.x = 0;
						garbageBox[i].size.y = 0;
					}
				}

				if (garbageBoxesCollected < 0)
				{
					garbageBoxesCollected = 0;
				}
				
			}
			else if (gamePaused)
			{
				timerON = false;

				for (int i = 0; i < maxButtons; i++)
				{
					if (CheckCollisionRecs({ mouse.position.x,  mouse.position.y, mouse.width, mouse.height }, { buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height }) || buttonSelect == i)
					{
						buttonSelect = i;
						buttons[i].defaultColor = RED;
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

			//---- GAME OVER CONDITION

			/*if (targetsLeft == 0)
			{
				gameON = false;
				timerON = false;
				buttonOption = buttonGameOver;
				isScreenFinished = true;
			}*/
		}

		void DrawGameplay()
		{
			DrawLevel();
			playerDraw();

			for (int i = 0; i < maxGarbageBoxes; i++)
			{
				DrawRectangle(garbageBox[i].pos.x, garbageBox[i].pos.y, garbageBox[i].size.x, garbageBox[i].size.y, garbageBox[i].color);
			}

			DrawRectangleLines(pauseButton.position.x, pauseButton.position.y, pauseButton.width, pauseButton.height, pauseButton.defaultColor);

			//DrawTextEx(sideFont, FormatText("Targets:%i", targetsLeft), { 20, 20 }, defaultFontSize / 1.5f, 1.0f, GREEN);
			//garbagePoints
			DrawTextEx(sideFont, FormatText("Collected:%i", garbageBoxesCollected), { 20, 15 }, defaultFontSize / 1.5f, 1.0f, RED);
			DrawTextEx(sideFont, FormatText("Points:%i", garbagePoints), {600, 15 }, defaultFontSize / 1.5f, 1.0f, RED);
			//DrawTextEx(sideFont, FormatText("Rotation:%i", player.rotation), { 20, 20 }, defaultFontSize / 1.5f, 1.0f, RED);
			DrawTextEx(mainFont,"II", { pauseButton.position.x + 13, pauseButton.position.y + 2 }, defaultFontSize/1.4f, 1.0f, pauseButton.defaultColor);
			

			if (!(gameON))
			{
				if (gamePaused)
				{
					//if(resolutionNormal) DrawTexturePro(pauseMenu, { 0, 0, (float)screenWidth / 4.2f, (float)screenHeight / 2.5f }, pauseBoxRec, { 0,0 }, 0, WHITE);
					//else if(resolutionSmall) DrawTexturePro(pauseMenu, { 0, 0, (float)screenWidth / 4.2f, (float)screenHeight / 2.5f }, pauseBoxRec, { 0,0 }, 0, WHITE);
					
					for (int i = 0; i < maxButtons; i++)
					{
						DrawRectangleLines(buttons[i].position.x, buttons[i].position.y, buttons[i].width, buttons[i].height, buttons[i].defaultColor);
					}
					DrawTextEx(mainFont, "PAUSED", { buttons[0].position.x - (screenWidth * 0.04f), 20 }, defaultFontSize, 1.0f, DARKGREEN);
					DrawTextEx(sideFont, "CONTINUE", { buttons[0].position.x + 10, buttons[0].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[0].defaultColor);
					DrawTextEx(sideFont, "RESTART", { buttons[1].position.x + 8, buttons[1].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[1].defaultColor);
					DrawTextEx(sideFont, "MENU", { buttons[2].position.x + 10, buttons[2].position.y + 5 }, defaultFontSize / 1.3, 1.0f, buttons[2].defaultColor);
				}
			}
		}

		void RestartPhase()
		{
			InitGameplayVariables();
			player.isAlive = true;
			buttonDistance = 0;
			gameON = true;
			timerON = true;
			garbageBoxesCollected = 0;
			garbagePoints = 0;
			//targetsLeft = 50;
		}

		bool FinishGameplayScreen()
		{
			buttonDistance = 0;
			return isScreenFinished;
		}

		void DeInitGameplayParallax()
		{
		}

		void DeInitGameplayResources()
		{

			#ifdef AUDIO
			StopSound(enemy_explode01);
			StopSound(ship_shoot01);
			UnloadSound(enemy_explode01);
			UnloadSound(ship_shoot01);
			#endif
		}
	}
}