#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"

namespace Juego
{
	const int maxGarbageBoxes = 6;
	enum obstacles
	{
		obMiddleSquare = 0,
		obMiddleSquare2,
		obMiddleSquare3,
		obMiddleSquare4,
		obMiddleSquare5,
		obMiddleSquare6,
		obMiddleSquare7,
		obMiddleSquare8,
		obMiddleSquare9,
		obMiddleSquare10,
		obDumpster,
		maxObstacles
	};

	struct obstacle
	{
		Vector2 pos;
		Vector2 size;
		Vector2 centre;
		float speed;
		bool isAlive;
		bool isOnPlayer;
		bool alreadyOnPlayer;
		Color color;
		float AccelerationRight;
		float AccelerationLeft;
		float AccelerationUp;
		float AccelerationDown;
		bool moveRight;
		bool moveLeft;
		bool moveUp;
		bool moveDown;
	};

	const int maxSpikes = 5;
	extern int currentLevel;
	extern int garbageBoxesCollected;
	//extern obstacle levelBackground;
	//extern obstacle levelMiddleSquare;
	extern obstacle obBackground;
	extern obstacle obstacles[maxObstacles];
	extern obstacle spikes[maxSpikes];
	extern obstacle exit;
	extern obstacle garbageBox[maxGarbageBoxes];

	namespace Gameplay_Section
	{
		void createLevelBackground();
		void createLevelObstacles();
		void DrawLevel();
	}
}

#endif // LEVEL_H
