#include "level.h"

#include "setup/game.h"

namespace Juego
{

	obstacle obBackground;
	obstacle obstacles[maxObstacles];
	obstacle garbageBox[maxGarbageBoxes];
	obstacle dumpster;
	obstacle fanArea1;
	obstacle fanArea2;

	Rectangle arm;

	Pendulum demo;

	int currentLevel = 0;
	int garbageBoxesCollected = 0;

	namespace Gameplay_Section
	{
		void createLevelBackground()
		{
			
		}

		void createLevelObstacles()
		{
			arm.height = 14;
			arm.width = 80;
			arm.x = screenWidth / 2 - 3;
			arm.y = screenHeight / 2 - 7;
			demo.color = BLACK;
			demo.radius = 40;
			demo.pos = { (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
			demo.angle = PI / 4;
			demo.angle2 = 7 * PI / 4;
			demo.length = 280;
			demo.aAcc = 0.0f;
			demo.aVel = 0.0f;
			demo.arm = arm;


			for (int i = 0;i < maxObstacles;i++)
			{
				obstacles[i].pos.x = 0;
				obstacles[i].pos.y = 0;
				obstacles[i].size.x = 0;
				obstacles[i].size.y = 0;
				obstacles[i].speed = 0;
				obstacles[i].isAlive = false;
				obstacles[i].color = BLANK;
			}

			obBackground.pos.x = 0 + 50;
			obBackground.pos.y = 0 + 50;
			obBackground.size.x = screenWidth - 100;
			obBackground.size.y = screenHeight - 100;
			obBackground.speed = 0;
			obBackground.isAlive = true;
			obBackground.color = WHITE;

			switch (currentLevel)
			{
			case 0:
			{

				for (int i = 0; i < maxGarbageBoxes; i++)
				{
					garbageBox[i].pos.x = (float)screenWidth / 2;
					garbageBox[i].pos.y = screenHeight / 2;
					garbageBox[i].size.x = 30;
					garbageBox[i].size.y = 30;
					garbageBox[i].speed = 0;
					garbageBox[i].isAlive = true;
					garbageBox[i].isOnPlayer = false;
					garbageBox[i].alreadyOnPlayer = false;
					garbageBox[i].color = BLACK;
					garbageBox[i].AccelerationRight = 0;
					garbageBox[i].AccelerationLeft = 0;
					garbageBox[i].AccelerationUp = 0;
					garbageBox[i].AccelerationDown = 0;
					garbageBox[i].moveDown = false;
					garbageBox[i].moveUp = false;
					garbageBox[i].moveLeft = false;
					garbageBox[i].moveRight = false;
				}

				garbageBox[0].pos.x = (float)screenWidth / 2;
				garbageBox[0].pos.y = screenHeight / 8.0f;

				garbageBox[1].pos.x = (float)screenWidth / 4;
				garbageBox[1].pos.y = screenHeight / 8.0f;

				garbageBox[2].pos.x = (float)screenWidth / 1.3f;
				garbageBox[2].pos.y = screenHeight / 8.0f;

				garbageBox[3].pos.x = (float)screenWidth / 4;
				garbageBox[3].pos.y = screenHeight / 1.2f;

				garbageBox[4].pos.x = (float)screenWidth / 2;
				garbageBox[4].pos.y = screenHeight / 1.2f;

				garbageBox[5].pos.x = (float)screenWidth / 1.3f;
				garbageBox[5].pos.y = screenHeight / 2.2f;

				obstacles[obMiddleSquare].pos.x = (float)screenWidth / 6;
				obstacles[obMiddleSquare].pos.y = screenHeight / 4;
				obstacles[obMiddleSquare].size.x = 250;
				obstacles[obMiddleSquare].size.y = 120;
				obstacles[obMiddleSquare].speed = 0;
				obstacles[obMiddleSquare].isAlive = true;
				obstacles[obMiddleSquare].color = BLACK;

				obstacles[obMiddleSquare2].pos.x = (float)screenWidth / 6;
				obstacles[obMiddleSquare2].pos.y = screenHeight / 1.6f;
				obstacles[obMiddleSquare2].size.x = 250;
				obstacles[obMiddleSquare2].size.y = 120;
				obstacles[obMiddleSquare2].speed = 0;
				obstacles[obMiddleSquare2].isAlive = true;
				obstacles[obMiddleSquare2].color = BLACK;

				obstacles[obMiddleSquare3].pos.x = (float)screenWidth / 1.55f;
				obstacles[obMiddleSquare3].pos.y = screenHeight / 4;
				obstacles[obMiddleSquare3].size.x = 250;
				obstacles[obMiddleSquare3].size.y = 120;
				obstacles[obMiddleSquare3].speed = 0;
				obstacles[obMiddleSquare3].isAlive = true;
				obstacles[obMiddleSquare3].color = BLACK;

				obstacles[obMiddleSquare4].pos.x = (float)screenWidth / 1.55f;
				obstacles[obMiddleSquare4].pos.y = screenHeight / 1.8f;
				obstacles[obMiddleSquare4].size.x = 250;
				obstacles[obMiddleSquare4].size.y = 120;
				obstacles[obMiddleSquare4].speed = 0;
				obstacles[obMiddleSquare4].isAlive = true;
				obstacles[obMiddleSquare4].color = BLACK;

				obstacles[obDumpster].pos.x = (float)screenWidth / 26;
				obstacles[obDumpster].pos.y = screenHeight / 2.2f;
				obstacles[obDumpster].size.x = 90;
				obstacles[obDumpster].size.y = 100;
				obstacles[obDumpster].speed = 0;
				obstacles[obDumpster].isAlive = true;
				obstacles[obDumpster].color = BLUE;

				obstacles[obMiddleSquare5].pos.x = (float)screenWidth / 1.55f;
				obstacles[obMiddleSquare5].pos.y = screenHeight / 1.07f;
				obstacles[obMiddleSquare5].size.x = 250;
				obstacles[obMiddleSquare5].size.y = 10;
				obstacles[obMiddleSquare5].speed = 0;
				obstacles[obMiddleSquare5].isAlive = true;
				obstacles[obMiddleSquare5].color = GRAY;

				obstacles[obMiddleSquare6].pos.x = (float)screenWidth / 6;
				obstacles[obMiddleSquare6].pos.y = screenHeight / 19.0f;
				obstacles[obMiddleSquare6].size.x = 250;
				obstacles[obMiddleSquare6].size.y = 10;
				obstacles[obMiddleSquare6].speed = 0;
				obstacles[obMiddleSquare6].isAlive = true;
				obstacles[obMiddleSquare6].color = GRAY;

				fanArea1.pos.x = (float)screenWidth / 1.55f;
				fanArea1.pos.y = screenHeight / 1.45f;
				fanArea1.size.x = 250;
				fanArea1.size.y = 200;
				fanArea1.speed = 0;
				fanArea1.isAlive = true;
				fanArea1.color = BLANK;

				fanArea2.pos.x = (float)screenWidth / 6;
				fanArea2.pos.y = screenHeight / 19.0f;
				fanArea2.size.x = 250;
				fanArea2.size.y = 150;
				fanArea2.speed = 0;
				fanArea2.isAlive = true;
				fanArea2.color = BLANK;

				obstacles[craneBase].pos.x = (float)screenWidth / 2 + 50;
				obstacles[craneBase].pos.y = screenHeight / 2 - 25;
				obstacles[craneBase].size.x = 70;
				obstacles[craneBase].size.y = 50;
				obstacles[craneBase].speed = 0;
				obstacles[craneBase].isAlive = true;
				obstacles[craneBase].color = BLACK;
			}
			break;
			}
		}

		void updatePendulum()
		{
			//demo.pos.y = (float)GetScreenHeight() / 2 + demo.length*sin(demo.angle);

			//demo.aAcc = -0.0000002*sin(demo.angle);

			//demo.angle += demo.aVel;
			//demo.angle2 += demo.aVel;
			//demo.aVel += demo.aAcc;

			////cout << demo.aVel << endl;
			//if (demo.aVel>0.00018 || demo.aVel<-0.00018)
			//{
			//	float auxradio;
			//	auxradio = demo.radius;
			//	demo.radius = auxradio;
			//	demo.color = BLACK;
			//}
			//else
			//{
			//	demo.radius = 0 + demo.length*cos(demo.angle2)*(0.2);
			//	//demo.color = Fade(RED, 0.7f);
			//}
				
		}

		void DrawLevel()
		{
			DrawRectangle(obBackground.pos.x, obBackground.pos.y, obBackground.size.x, obBackground.size.y, obBackground.color);
			DrawRectangle(dumpster.pos.x, dumpster.pos.y, dumpster.size.x, dumpster.size.y, dumpster.color);
			DrawRectangle(fanArea1.pos.x, fanArea1.pos.y, fanArea1.size.x, fanArea1.size.y, fanArea1.color);
			DrawRectangle(fanArea2.pos.x, fanArea2.pos.y, fanArea2.size.x, fanArea2.size.y, fanArea2.color);

			for (int i = 0; i < maxObstacles; i++)
			{
				DrawRectangle(obstacles[i].pos.x, obstacles[i].pos.y, obstacles[i].size.x, obstacles[i].size.y, obstacles[i].color);
			}

			if (currentLevel > 2)
			{
				DrawTextEx(mainFont, "THANKS FOR PLAYING", { screenWidth / 9.0f, screenHeight / 2.0f }, defaultFontSize / 1.2f, 1.0f, GREEN);
				DrawTextEx(mainFont, "OUR DEMO", { screenWidth / 7.0f, screenHeight / 1.5f }, defaultFontSize / 1.2f, 1.0f, GREEN);
			}
		}

		void DrawArm()
		{
			DrawRectangleRec(demo.arm, GRAY);
			DrawLineEx({ (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 }, { demo.pos.x, demo.pos.y }, 3, GRAY);
		}
	}
}