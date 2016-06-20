#include "gamelogic.h"

GameLogic::GameLogic(){
	this->rounds = 8;
	this->currentRound = 0;
	this->readyToPlay = false;
	this->currentStone = NULL;
}

void GameLogic::startRound(){

	//place Camera
	//Select player
	//instantiate Stone
	Vector3* startingPos = new Vector3(0, 0, 0);
	this->currentStone = new Stone(startingPos,this->currentRound%2);

	this->stone_list.push_back(this->currentStone);
	go_list.push_back((GameObject*)this->currentStone);

	//Controls
	this->readyToPlay = true;
	//unlock controls
	//wait for input
}

void GameLogic::throwStone(){
	this->currentStone->mov->x = (rand()%100 - 50)*0.003;
	this->currentStone->mov->z = (rand()%100 + 50)*0.01;
	this->currentStone->ang_mov->y = (rand()%100 - 50)*0.01;

	this->readyToPlay = false;
}

void GameLogic::endRound(){
	//calcscores
	this->currentRound += 1;
	if(this->currentRound < this->rounds)
		this->startRound();
	else
		;//endgame
}

void GameLogic::update(){
	if(readyToPlay)
		return;

	for(int i = 0; i < (int)stone_list.size(); i++){
		Stone* s = stone_list[i];

		if(s->mov->x != 0 || s->mov->z != 0)
			return;
	}

	//Caso não esteja numa ronda e não haja nenhuma peça a mover
	this->endRound();
}

Stone* GameLogic::getClosestStone(){
	if(this->currentRound == 0)
		return NULL;

	Stone* s = NULL;
	float shortest_d = 100;
	float d;

	for(int i = 0; i < (int)stone_list.size(); i++){

		Stone* t = stone_list[i];

		float dx = 0 - t->pos->x;
		float dz = 40 - t->pos->z;

		d = sqrt(dx*dx + dz*dz);

		if(d < shortest_d){
			shortest_d = d;
			s = t;
		}
	}
	return s;
}
