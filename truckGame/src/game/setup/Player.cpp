#include "Player.h"

#include "Setup\game.h"
#include "setup/level.h"
#include "Screens\settings.h"
#include "Screens\gameplay.h"

namespace Juego
{
	cube playerhitbox;
	cube player;
	cube playerfront;
	static float playerAccelerationLeft = 0;
	static float playerAccelerationRight = 0;
	static float playerAccelerationUp = 0;
	static float playerAccelerationDown = 0;

	static int collisionFix = 0;
	static int collisionFix2 = 0;
	static bool currentlyTouching = false;

	bool moveRight = false;
	bool moveRightBox = false;
	bool moveLeft = false;
	bool moveLeftBox = false;
	bool moveUp = false;
	bool moveUpBox = false;
	bool moveDown = false;
	bool moveDownBox = false;

	int lastBoxCollected = 0;

	namespace Gameplay_Section
	{
		void createPlayer()
		{
			if (resolutionNormal) 
			{
				player.size = { 80, 100 };
				playerhitbox.size = { 100, 100 };
				player.defaultSpeed = 500.0f;
				playerfront.size = { 80, 30 };
				collisionFix = player.size.y/2;
				collisionFix2 = 30;
			}
			else if (resolutionSmall) 
			{
				player.size = { 50 / resolutionSizeFix, 50 / resolutionSizeFix };
				player.defaultSpeed = 500.0f / resolutionSizeFix;
				player.centre = { player.size.x / 2,player.size.y / 2 };
			}
			if (currentLevel == 0)
			{
				player.position = { (float)screenWidth / 6, (float)screenHeight / 1.9f };
				playerfront.position = { (float)screenWidth / 6, (float)screenHeight / 1.9f };
				playerhitbox.position = { (float)screenWidth / 6 - playerhitbox.size.x / 2, (float)screenHeight / 1.9f - playerhitbox.size.y / 2 };
			}
			else if(currentLevel == 1) player.position = { (float)screenWidth / 10, obBackground.pos.y + obBackground.size.y - player.size.y};
			else if(currentLevel == 2) player.position = { (float)screenWidth / 10, obBackground.pos.y + player.size.y };
			player.isAlive = true;
			player.inputActive = false;
			player.rotation = 0;
			player.textureTint = DARKGRAY;
			player.lives = 10;
			playerhitbox.isAlive = true;
			playerhitbox.inputActive = false;
			playerhitbox.rotation = 0;
			playerhitbox.textureTint = BLANK;
			playerfront.isAlive = true;
			playerfront.inputActive = false;
			playerfront.rotation = 0;
			playerfront.textureTint = SKYBLUE;
		}

		void playerInput()
		{
			if (IsKeyDown(playerKeys[REVERSE]))
			{
				PlayMusicStream(engineReverse);
				UpdateMusicStream(engineReverse);
				StopMusicStream(engineRunOff);
				StopMusicStream(engineRun);

				if (player.rotation == 90)
				{
					playerAccelerationLeft = playerAccelerationLeft + 0.25f;

					if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
					else playerAccelerationRight = playerAccelerationRight - 0.25f;

					if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
					else playerAccelerationUp = playerAccelerationUp - 0.35f;
					if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
					else playerAccelerationDown = playerAccelerationDown - 0.35f;
				}

				if (player.rotation == 270)
				{
					playerAccelerationRight = playerAccelerationRight + 0.25f;

					if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
					else playerAccelerationLeft = playerAccelerationLeft - 0.25f;

					if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
					else playerAccelerationUp = playerAccelerationUp - 0.35f;
					if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
					else playerAccelerationDown = playerAccelerationDown - 0.35f;
				}

				if (player.rotation == 180)
				{
					playerAccelerationUp = playerAccelerationUp + 0.25f;

					if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
					else playerAccelerationDown = playerAccelerationDown - 0.25f;

					if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
					else playerAccelerationLeft = playerAccelerationLeft - 0.35f;
					if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
					else playerAccelerationRight = playerAccelerationRight - 0.35f;
				}

				if (player.rotation == 0)
				{
					playerAccelerationDown = playerAccelerationDown + 0.25f;

					if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
					else playerAccelerationUp = playerAccelerationUp - 0.25f;

					if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
					else playerAccelerationLeft = playerAccelerationLeft - 0.35f;
					if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
					else playerAccelerationRight = playerAccelerationRight - 0.35f;
				}
			}
			else if (IsKeyDown(playerKeys[UP]))
			{
				PlayMusicStream(engineRun);
				UpdateMusicStream(engineRun);
				StopMusicStream(engineRunOff);
				StopMusicStream(engineReverse);

					player.rotation = 0;
					playerAccelerationUp = playerAccelerationUp + 0.25f;

					if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
					else playerAccelerationDown = playerAccelerationDown - 0.25f;
					
					if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
					else playerAccelerationLeft = playerAccelerationLeft - 0.35f;
					if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
					else playerAccelerationRight = playerAccelerationRight - 0.35f;					
			}
			else if (IsKeyDown(playerKeys[DOWN]))
			{
				PlayMusicStream(engineRun);
				UpdateMusicStream(engineRun);
				StopMusicStream(engineRunOff);
				StopMusicStream(engineReverse);

					player.rotation = 180;
					playerAccelerationDown = playerAccelerationDown + 0.25f;

					if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
					else playerAccelerationUp = playerAccelerationUp - 0.25f;

					if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
					else playerAccelerationLeft = playerAccelerationLeft - 0.35f;
					if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
					else playerAccelerationRight = playerAccelerationRight - 0.35f;
			}
			else if (IsKeyDown(playerKeys[RIGHT]))
			{
				PlayMusicStream(engineRun);
				UpdateMusicStream(engineRun);
				StopMusicStream(engineRunOff);
				StopMusicStream(engineReverse);

				player.rotation = 90;
				playerAccelerationRight = playerAccelerationRight + 0.25f;

				if (playerAccelerationLeft <= 0) playerAccelerationLeft = 0;
				else playerAccelerationLeft = playerAccelerationLeft - 0.25f;
				
				if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
				else playerAccelerationUp = playerAccelerationUp - 0.35f;
				if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
				else playerAccelerationDown = playerAccelerationDown - 0.35f;
			}
			else if (IsKeyDown(playerKeys[LEFT]))
			{
				PlayMusicStream(engineRun);
				UpdateMusicStream(engineRun);
				StopMusicStream(engineRunOff);
				StopMusicStream(engineReverse);

				player.rotation = 270;
				playerAccelerationLeft = playerAccelerationLeft + 0.25f;

				if (playerAccelerationRight <= 0) playerAccelerationRight = 0;
				else playerAccelerationRight = playerAccelerationRight - 0.25f;

				if (playerAccelerationUp <= 0) playerAccelerationUp = 0;
				else playerAccelerationUp = playerAccelerationUp - 0.35f;
				if (playerAccelerationDown <= 0) playerAccelerationDown = 0;
				else playerAccelerationDown = playerAccelerationDown - 0.35f;
			}
			else 
			{
				
				StopMusicStream(engineMax);
				StopMusicStream(engineRun);
				StopMusicStream(engineReverse);

				if (playerAccelerationLeft <= 0)
				{
					playerAccelerationLeft = 0;
				}
				else
				{
					PlayMusicStream(engineRunOff);
					UpdateMusicStream(engineRunOff);
					
					playerAccelerationLeft = playerAccelerationLeft - 0.25f;
				}

				if (playerAccelerationRight <= 0)
				{
					playerAccelerationRight = 0;
				}
				else
				{
					PlayMusicStream(engineRunOff);
					UpdateMusicStream(engineRunOff);
					playerAccelerationRight = playerAccelerationRight - 0.25f;
				}

				if (playerAccelerationUp <= 0)
				{
					playerAccelerationUp = 0;
				}
				else
				{
					PlayMusicStream(engineRunOff);
					UpdateMusicStream(engineRunOff);
					playerAccelerationUp = playerAccelerationUp - 0.25f;
				}

				if (playerAccelerationDown <= 0)
				{
					playerAccelerationDown = 0;
				}
				else
				{
					PlayMusicStream(engineRunOff);
					UpdateMusicStream(engineRunOff);
					playerAccelerationDown = playerAccelerationDown - 0.25f;
				}
			}
		}

		void checkImpulseBox()
		{
			for (int i = maxGarbageBoxes; i >= 0; i--)
			{
				if (garbageBox[i].alreadyOnPlayer && garbageBox[i].isOnPlayer && garbageBox[i].isAlive)
				{
					if (player.rotation == 180 && moveUp)
					{
						garbageBox[i].moveUp = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationUp = playerAccelerationDown * 2.0f;
						i = -1;
					}

					if (player.rotation == 0 && moveDown)
					{
						garbageBox[i].moveDown = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationDown = playerAccelerationUp * 2.0f;
						i = -1;
					}

					if (player.rotation == 270 && moveRight)
					{
						garbageBox[i].moveRight = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationRight = playerAccelerationLeft * 2.0f;
						i = -1;
					}

					if (player.rotation == 90 && moveLeft)
					{
						garbageBox[i].moveLeft = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationLeft = playerAccelerationRight * 2.0f;
						i = -1;
					}

					if (player.rotation == 180 && moveDown)
					{
						garbageBox[i].moveUp = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationUp = playerAccelerationUp * 2.0f;
						i = -1;
					}

					if (player.rotation == 0 && moveUp)
					{
						garbageBox[i].moveDown = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationDown = playerAccelerationDown * 2.0f;
						i = -1;
					}

					if (player.rotation == 90 && moveRight)
					{
						garbageBox[i].moveLeft = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationLeft = playerAccelerationLeft * 2.0f;
						i = -1;
					}

					if (player.rotation == 270 && moveLeft)
					{
						garbageBox[i].moveRight = true;
						garbageBox[i].isOnPlayer = false;
						garbageBox[i].alreadyOnPlayer = false;
						garbageBox[i].AccelerationRight = playerAccelerationRight * 2.0f;
						i = -1;
					}
				}
			}
		}

		void playerUpdate()
		{
			for (int i = 0; i < maxGarbageBoxes; i++)
			{

				if (CheckCollisionRecs({ playerhitbox.position.x,playerhitbox.position.y,playerhitbox.size.x,playerhitbox.size.y }, { garbageBox[i].pos.x ,garbageBox[i].pos.y,garbageBox[i].size.x,garbageBox[i].size.y }) && (garbageBox[i].AccelerationUp <= 0 && garbageBox[i].AccelerationDown <= 0 && garbageBox[i].AccelerationLeft <= 0 && garbageBox[i].AccelerationRight <= 0))
				{
					if (!garbageBox[i].alreadyOnPlayer)
					{
						garbageBoxesCollected++;
						garbageBox[i].isOnPlayer = true;
						garbageBox[i].alreadyOnPlayer = true;
					}
				}
				else
				{
					garbageBox[i].isOnPlayer = false;
					garbageBox[i].alreadyOnPlayer = false;
				}
			}

			playerhitbox.position.x += playerAccelerationRight * GetFrameTime();
			playerhitbox.position.x -= playerAccelerationLeft * GetFrameTime();
			playerhitbox.position.y += playerAccelerationDown * GetFrameTime();
			playerhitbox.position.y -= playerAccelerationUp * GetFrameTime();

			player.position.y = playerhitbox.position.y + collisionFix; //+ collisionFix;
			player.position.x = playerhitbox.position.x + collisionFix; //+ collisionFix;
			playerfront.position.y = playerhitbox.position.y + collisionFix;
			playerfront.position.x = playerhitbox.position.x + collisionFix;

			if (playerAccelerationLeft >= player.defaultSpeed)
			{
				if (!(IsMusicPlaying(engineReverse)))
				{
					PlayMusicStream(engineMax);
					UpdateMusicStream(engineMax);
					StopMusicStream(engineRunOff);
					StopMusicStream(engineRun);
				}
				playerAccelerationLeft = player.defaultSpeed;
			}
			if (playerAccelerationRight >= player.defaultSpeed)
			{
				if (!(IsMusicPlaying(engineReverse)))
				{
					PlayMusicStream(engineMax);
					UpdateMusicStream(engineMax);
					StopMusicStream(engineRunOff);
					StopMusicStream(engineRun);
				}
				playerAccelerationRight = player.defaultSpeed;
			}
			if (playerAccelerationDown >= player.defaultSpeed)
			{
				if (!(IsMusicPlaying(engineReverse)))
				{
					PlayMusicStream(engineMax);
					UpdateMusicStream(engineMax);
					StopMusicStream(engineRunOff);
					StopMusicStream(engineRun);
				}
				playerAccelerationDown = player.defaultSpeed;
			}
			if (playerAccelerationUp >= player.defaultSpeed)
			{
				if (!(IsMusicPlaying(engineReverse)))
				{
					PlayMusicStream(engineMax);
					UpdateMusicStream(engineMax);
					StopMusicStream(engineRunOff);
					StopMusicStream(engineRun);
				}
				playerAccelerationUp = player.defaultSpeed;
			}

			//////////////////////////////////--------------------------

			if (CheckCollisionRecs({ playerhitbox.position.x,playerhitbox.position.y,playerhitbox.size.x,playerhitbox.size.y }, { fanArea1.pos.x ,fanArea1.pos.y,fanArea1.size.x,fanArea1.size.y }))
			{
				playerhitbox.position.y -= 25.0f * GetFrameTime();
			}

			if (CheckCollisionRecs({ playerhitbox.position.x,playerhitbox.position.y,playerhitbox.size.x,playerhitbox.size.y }, { fanArea2.pos.x ,fanArea2.pos.y,fanArea2.size.x,fanArea2.size.y }))
			{
				playerhitbox.position.y += 25.0f * GetFrameTime();
			}

			if (CheckCollisionCircleRec(demo.pos, demo.radius, { playerhitbox.position.x,playerhitbox.position.y,playerhitbox.size.x,playerhitbox.size.y }))
			{
				if (playerhitbox.position.x + playerhitbox.size.x > demo.pos.x - demo.radius && playerhitbox.position.x + playerhitbox.size.x < demo.pos.x && playerhitbox.position.y + playerhitbox.size.y > demo.pos.y - demo.radius + 0.5f && playerhitbox.position.y < demo.pos.y + demo.radius - 0.5f)
				{
					moveLeft = true;
					checkImpulseBox();
					if (!(currentlyTouching))
					{
						PlaySound(crash);
						garbageBoxesCollected--;
						player.lives--;
						currentlyTouching = true;
					}

					playerAccelerationLeft = playerAccelerationRight;

					playerAccelerationRight = 0;
					player.position.x = demo.pos.x - demo.radius - player.size.x + collisionFix2;
					playerhitbox.position.x = demo.pos.x - demo.radius - playerhitbox.size.x;
				}


				if (playerhitbox.position.x < demo.pos.x + demo.radius && playerhitbox.position.x > demo.pos.x && playerhitbox.position.y + playerhitbox.size.y > demo.pos.y - demo.radius + 0.5f && playerhitbox.position.y < demo.pos.y + demo.radius - 0.5f)
				{
					moveRight = true;
					checkImpulseBox();
					if (!(currentlyTouching))
					{
						PlaySound(crash);
						garbageBoxesCollected--;
						player.lives--;
						currentlyTouching = true;
					}

					playerAccelerationRight = playerAccelerationLeft;

					playerAccelerationLeft = 0;

					player.position.x = demo.pos.x + demo.radius + collisionFix;
					playerhitbox.position.x = demo.pos.x + demo.radius;
				}

				if (playerhitbox.position.y + playerhitbox.size.y > demo.pos.y - demo.radius && playerhitbox.position.y + playerhitbox.size.y < demo.pos.y && playerhitbox.position.x + playerhitbox.size.x > demo.pos.x - demo.radius + 0.1f && playerhitbox.position.x < demo.pos.x + demo.radius - 0.1f)
				{
					moveUp = true;
					checkImpulseBox();
					if (!(currentlyTouching))
					{
						PlaySound(crash);
						garbageBoxesCollected--;
						player.lives--;
						currentlyTouching = true;
					}
					playerAccelerationUp = playerAccelerationDown;

					playerAccelerationDown = 0;
					player.position.y = demo.pos.y - demo.radius - player.size.y + collisionFix;
					playerhitbox.position.y = demo.pos.y - demo.radius - playerhitbox.size.y;
				}


				if (playerhitbox.position.y <= demo.pos.y + demo.radius && playerhitbox.position.y > demo.pos.y && playerhitbox.position.x + playerhitbox.size.x > demo.pos.x - demo.radius + 0.1f && playerhitbox.position.x < demo.pos.x + demo.radius - 0.1f)
				{
					moveDown = true;
					checkImpulseBox();
					if (!(currentlyTouching))
					{
						PlaySound(crash);
						garbageBoxesCollected--;
						player.lives--;
						currentlyTouching = true;
					}
					playerAccelerationDown = playerAccelerationUp;

					playerAccelerationUp = 0;
					player.position.y = demo.pos.y + demo.radius + collisionFix;
					playerhitbox.position.y = demo.pos.y + demo.radius;
				}
			}

			for (int i = 0; i < maxObstacles; i++)
			{
				if (CheckCollisionRecs({ playerhitbox.position.x,playerhitbox.position.y,playerhitbox.size.x,playerhitbox.size.y }, { obstacles[i].pos.x ,obstacles[i].pos.y,obstacles[i].size.x,obstacles[i].size.y }))
				{
					if (playerhitbox.position.x + playerhitbox.size.x > obstacles[i].pos.x && playerhitbox.position.x + playerhitbox.size.x < obstacles[i].pos.x + (obstacles[i].size.x / 2) && playerhitbox.position.y + playerhitbox.size.y > obstacles[i].pos.y + 0.5f && playerhitbox.position.y < obstacles[i].pos.y + obstacles[i].size.y - 0.5f)
					{
						moveLeft = true;
						checkImpulseBox();
						if (!(currentlyTouching))
						{
							PlaySound(crash);
							garbageBoxesCollected--;
							player.lives--;
							currentlyTouching = true;
						}

						playerAccelerationLeft = playerAccelerationRight;

						playerAccelerationRight = 0;
						player.position.x = obstacles[i].pos.x - player.size.x + collisionFix2;
						playerhitbox.position.x = obstacles[i].pos.x - playerhitbox.size.x;
					}

					if (playerhitbox.position.x < obstacles[i].pos.x + obstacles[i].size.x && playerhitbox.position.x > obstacles[i].pos.x + (obstacles[i].size.x / 2) && playerhitbox.position.y + playerhitbox.size.y > obstacles[i].pos.y + 0.5f && playerhitbox.position.y < obstacles[i].pos.y + obstacles[i].size.y - 0.5f)
					{
						moveRight = true;
						checkImpulseBox();
						if (!(currentlyTouching))
						{
							PlaySound(crash);
							garbageBoxesCollected--;
							player.lives--;
							currentlyTouching = true;
						}

						playerAccelerationRight = playerAccelerationLeft;

						playerAccelerationLeft = 0;

						player.position.x = obstacles[i].pos.x + obstacles[i].size.x + collisionFix;
						playerhitbox.position.x = obstacles[i].pos.x + obstacles[i].size.x;
					}

					if (playerhitbox.position.y + playerhitbox.size.y > obstacles[i].pos.y && playerhitbox.position.y + playerhitbox.size.y < obstacles[i].pos.y + (obstacles[i].size.y / 2) && playerhitbox.position.x + playerhitbox.size.x > obstacles[i].pos.x + 0.1f && playerhitbox.position.x < obstacles[i].pos.x + obstacles[i].size.x - 0.1f)
					{
						moveUp = true;
						checkImpulseBox();
						if (!(currentlyTouching))
						{
							PlaySound(crash);
							garbageBoxesCollected--;
							player.lives--;
							currentlyTouching = true;
						}
						playerAccelerationUp = playerAccelerationDown;

						playerAccelerationDown = 0;
						player.position.y = obstacles[i].pos.y - player.size.y + collisionFix;
						playerhitbox.position.y = obstacles[i].pos.y - playerhitbox.size.y;
					}

					if (playerhitbox.position.y <= obstacles[i].pos.y + obstacles[i].size.y && playerhitbox.position.y > obstacles[i].pos.y + (obstacles[i].size.y / 2) && playerhitbox.position.x + playerhitbox.size.x > obstacles[i].pos.x + 0.1f && playerhitbox.position.x < obstacles[i].pos.x + obstacles[i].size.x - 0.1f)
					{
						moveDown = true;
						checkImpulseBox();
						if (!(currentlyTouching))
						{
							PlaySound(crash);
							garbageBoxesCollected--;
							player.lives--;
							currentlyTouching = true;
						}
						playerAccelerationDown = playerAccelerationUp;

						playerAccelerationUp = 0;
						player.position.y = obstacles[i].pos.y + obstacles[i].size.y + collisionFix;
						playerhitbox.position.y = obstacles[i].pos.y + obstacles[i].size.y;
					}

					player.textureTint = YELLOW;
				}
				else
				{
					
				}

				player.textureTint = GRAY;
				currentlyTouching = false;

				for (int j = 0; j < maxGarbageBoxes; j++)
				{
					if (CheckCollisionRecs({ garbageBox[j].pos.x,garbageBox[j].pos.y,garbageBox[j].size.x,garbageBox[j].size.y }, { obstacles[i].pos.x ,obstacles[i].pos.y,obstacles[i].size.x,obstacles[i].size.y }))
					{
						if (garbageBox[j].pos.x + garbageBox[j].size.x > obstacles[j].pos.x && garbageBox[j].pos.x + playerhitbox.size.x < obstacles[i].pos.x + (obstacles[i].size.x / 2) && garbageBox[j].pos.y + garbageBox[j].size.y > obstacles[i].pos.y + 0.5f && garbageBox[j].pos.y < obstacles[i].pos.y + obstacles[i].size.y - 0.5f)
						{
							garbageBox[j].pos.x = obstacles[i].pos.x - garbageBox[j].size.x;
						}

						if (garbageBox[j].pos.x < obstacles[i].pos.x + obstacles[i].size.x && garbageBox[j].pos.x > obstacles[i].pos.x + (obstacles[i].size.x / 2) && garbageBox[j].pos.y + garbageBox[j].size.y > obstacles[i].pos.y + 0.5f && garbageBox[j].pos.y < obstacles[i].pos.y + obstacles[i].size.y - 0.5f)
						{
							garbageBox[j].pos.x = obstacles[i].pos.x + obstacles[i].size.x;
						}

						if (garbageBox[j].pos.y + garbageBox[j].size.y > obstacles[i].pos.y && garbageBox[j].pos.y + garbageBox[j].size.y < obstacles[i].pos.y + (obstacles[i].size.y / 2) && garbageBox[j].pos.x + garbageBox[j].size.x > obstacles[i].pos.x + 0.1f && garbageBox[j].pos.x < obstacles[i].pos.x + obstacles[i].size.x - 0.1f)
						{
							garbageBox[j].pos.y = obstacles[i].pos.y - garbageBox[j].size.y;
						}

						if (garbageBox[j].pos.y <= obstacles[i].pos.y + obstacles[i].size.y && garbageBox[j].pos.y > obstacles[i].pos.y + (obstacles[i].size.y / 2) && garbageBox[j].pos.x + garbageBox[j].size.x > obstacles[i].pos.x + 0.1f && garbageBox[j].pos.x < obstacles[i].pos.x + obstacles[i].size.x - 0.1f)
						{
							garbageBox[j].pos.y = obstacles[i].pos.y + obstacles[i].size.y;
						}
					}
				}

				
			}

			if (moveRight)
			{
				if (playerAccelerationRight <= 0)
				{
					moveRight = false;
					playerAccelerationRight = 0;
				}
				else playerAccelerationRight = playerAccelerationRight - 0.25f;
			}

			if (moveLeft)
			{
				if (playerAccelerationLeft <= 0)
				{
					moveLeft = false;
					playerAccelerationLeft = 0;
				}
				else playerAccelerationLeft = playerAccelerationLeft - 0.25f;
			}

			if (moveUp)
			{
				if (playerAccelerationUp <= 0)
				{
					moveUp = false;
					playerAccelerationUp = 0;
				}
				else playerAccelerationUp = playerAccelerationUp - 0.25f;
			}

			if (moveDown)
			{
				if (playerAccelerationDown <= 0)
				{
					moveDown = false;
					playerAccelerationDown = 0;
				}
				else playerAccelerationDown = playerAccelerationDown - 0.25f;
			}

			for (int i = 0; i < maxGarbageBoxes; i++)
			{
				if (garbageBox[i].moveRight)
				{
					if (garbageBox[i].AccelerationRight <= 0)
					{
						garbageBox[i].moveRight = false;
						garbageBox[i].AccelerationRight = 0;
					}
					else garbageBox[i].AccelerationRight = garbageBox[i].AccelerationRight - 0.35f;
				}

				if (garbageBox[i].moveLeft)
				{

					if (garbageBox[i].AccelerationLeft <= 0)
					{
						garbageBox[i].moveLeft = false;
						garbageBox[i].AccelerationLeft = 0;
					}
					else garbageBox[i].AccelerationLeft = garbageBox[i].AccelerationLeft - 0.35f;
				}

				if (garbageBox[i].moveUp)
				{
					if (garbageBox[i].AccelerationUp <= 0)
					{
						garbageBox[i].moveUp = false;
						garbageBox[i].AccelerationUp = 0;
					}
					else garbageBox[i].AccelerationUp = garbageBox[i].AccelerationUp - 0.35f;
				}

				if (garbageBox[i].moveDown)
				{
					if (garbageBox[i].AccelerationDown <= 0)
					{
						garbageBox[i].moveDown = false;
						garbageBox[i].AccelerationDown = 0;
					}
					else garbageBox[i].AccelerationDown = garbageBox[i].AccelerationDown - 0.35f;
				}
			}

			//////////////////////////////////--------------------------

			for (int j = 0; j < maxGarbageBoxes; j++)
			{
				if (garbageBox[j].pos.y + garbageBox[j].size.y > obBackground.pos.y + obBackground.size.y)
				{
					garbageBox[j].pos.y = obBackground.pos.y + obBackground.size.y - garbageBox[j].size.y;
				}

				if (garbageBox[j].pos.y < obBackground.pos.y)
				{
					garbageBox[j].pos.y = obBackground.pos.y;
				}

				if (garbageBox[j].pos.x + garbageBox[j].size.x > obBackground.pos.x + obBackground.size.x)
				{
					garbageBox[j].pos.x = obBackground.pos.x + obBackground.size.x - garbageBox[j].size.x;
				}

				if (garbageBox[j].pos.x <= obBackground.pos.x)
				{
					garbageBox[j].pos.x = obBackground.pos.x;
				}
			}

			if (playerhitbox.position.y + playerhitbox.size.y > obBackground.pos.y + obBackground.size.y)
			{
				moveUp = true;
				//checkImpulseBoxUp();
				checkImpulseBox();
				if (!(currentlyTouching))
				{
					PlaySound(crash);
					garbageBoxesCollected--;
					player.lives--;
					currentlyTouching = true;
				}
				playerAccelerationUp = playerAccelerationDown;

				playerAccelerationDown = 0;
				player.position.y = obBackground.pos.y + obBackground.size.y - player.size.y + collisionFix;
				playerhitbox.position.y = obBackground.pos.y + obBackground.size.y - playerhitbox.size.y;
			}

			if (playerhitbox.position.y < obBackground.pos.y)
			{
				moveDown = true;
				checkImpulseBox();
				if (!(currentlyTouching))
				{
					PlaySound(crash);
					garbageBoxesCollected--;
					player.lives--;
					currentlyTouching = true;
				}
				playerAccelerationDown = playerAccelerationUp;

				playerAccelerationUp = 0;
				player.position.y = obBackground.pos.y + collisionFix;
				playerhitbox.position.y = obBackground.pos.y;
			}

			if (playerhitbox.position.x + playerhitbox.size.x > obBackground.pos.x + obBackground.size.x)
			{
				moveLeft = true;
				checkImpulseBox();
				if (!(currentlyTouching))
				{
					PlaySound(crash);
					garbageBoxesCollected--;
					player.lives--;
					currentlyTouching = true;
				}
				playerAccelerationLeft = playerAccelerationRight;

				playerAccelerationRight = 0;
				player.position.x = obBackground.pos.x + obBackground.size.x - player.size.x + collisionFix2;
				playerhitbox.position.x = obBackground.pos.x + obBackground.size.x - playerhitbox.size.x;
			}

			if (playerhitbox.position.x <= obBackground.pos.x)
			{
				moveRight = true;
				checkImpulseBox();
				if (!(currentlyTouching))
				{
					PlaySound(crash);
					garbageBoxesCollected--;
					player.lives--;
					currentlyTouching = true;
				}
				playerAccelerationRight = playerAccelerationLeft;

				playerAccelerationLeft = 0;

				player.position.x = obBackground.pos.x + collisionFix;
				playerhitbox.position.x = obBackground.pos.x;		
			}

			currentlyTouching = false;
			
		}

		void playerDraw()
		{
			if (resolutionNormal)
			{

				//DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, player.textureTint);
				DrawRectanglePro({ playerhitbox.position.x, playerhitbox.position.y, playerhitbox.size.x, playerhitbox.size.y }, { 0,0 },0, playerhitbox.textureTint);
				DrawRectanglePro({ player.position.x, player.position.y, player.size.x, player.size.y }, {40,50}, player.rotation, player.textureTint);
				DrawRectanglePro({ playerfront.position.x, playerfront.position.y, playerfront.size.x, playerfront.size.y }, { 40,50 }, player.rotation, playerfront.textureTint);
			}
			else if (resolutionSmall)
			{

				DrawRectangle(player.position.x, player.position.y, player.size.x, player.size.y, player.textureTint);
			}
		}
	}
}