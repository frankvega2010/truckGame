#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace Juego
{
	enum gameplayOptions 
	{
		buttonContinue = 20,
		buttonRestart,
		buttonGameOver,
		buttonQuitToMenu
	};

	enum playerKeysNumber
	{
		UP = 8,
		RIGHT,
		REVERSE,
		DOWN,
		LEFT,
		MAX
	};


	extern bool gameON;
	extern int playerKeys[MAX];
	extern int garbagePoints;
	extern Music engineMax;
	extern Music engineRun;
	extern Music engineRunOff;
	extern Music engineReverse;
	extern Sound crash;

	namespace Gameplay_Section
	{
		void InitGameplayVariables();
		void InitGameplayParallax();
		void InitGameplayScreen();
		void UpdateGameplayScreen();
		void DrawGameplay();
		void RestartPhase();
		bool FinishGameplayScreen();
		void DeInitGameplayParallax();
		void DeInitGameplayResources();
	}
}
#endif // GAMEPLAY_H