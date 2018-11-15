#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace Juego
{
	struct cube
	{
		Vector2 position;
		Vector2 size;
		int rotation;
		float defaultSpeed;
		Vector2 centre;
		bool isAlive;
		bool inputActive;
		Color textureTint;
	};

	struct Circle {
		Vector2 position;
		Vector2 speed;
		int radius;
		bool active;
	};

	extern cube player;
	extern cube playerhitbox;
	extern cube playerfront;
	extern int lastBoxCollected;

	//extern float garbageAccelerationLeft;
	//extern float garbageAccelerationRight;
	//extern float garbageAccelerationUp;
	//extern float garbageAccelerationDown;

	namespace Gameplay_Section
	{
		void createPlayer();
		void playerInput();
		void playerUpdate();
		void playerDraw();
	}
}
#endif // PLAYER_H
