#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>

#include "raylib.h"

using namespace std;

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
		craneBase,
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

	struct Pendulum
	{
		float radius;
		Rectangle arm;
		Color color;
		Vector2 pos;
		float length;
		float angle;
		float aVel;
		float aAcc;
		float angle2;
	};

	extern int currentLevel;
	extern int garbageBoxesCollected;

	extern obstacle obBackground;
	extern obstacle obstacles[maxObstacles];
	extern obstacle garbageBox[maxGarbageBoxes];
	extern obstacle fanArea1;
	extern obstacle fanArea2;
	extern Pendulum demo;

	namespace Gameplay_Section
	{
		void createLevelBackground();
		void createLevelObstacles();
		void updatePendulum();
		void DrawLevel();
		void DrawArm();
	}
}

#endif // LEVEL_H
