#include "gameobject.h"
#include "objects.h"

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

class GameLogic{
	public:
		Field* field;
		int rounds;
		int currentRound;
		bool readyToPlay;
		Stone* currentStone;

		vector<Stone*> stone_list;
		//Camera cam_list[3];

		GameLogic();
		void startRound();
		void throwStone();
		void endRound();
		void update();
		Stone* getClosestStone();

};

extern GameLogic* game;

#endif
