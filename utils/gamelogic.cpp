#include "gamelogic.h"


GameLogic::GameLogic(GLint maxRounds,Vector3* buttonCenter, GLfloat houseDiameter){
	this->maxRounds=maxRounds;
	this->buttonCenter=buttonCenter;
	this->houseDiameter=houseDiameter;
	this->player1Points=0;
	this->player2Points=0;
	this->currentRound=0;
}