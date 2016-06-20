
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "gameobject.h"

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

class GameLogic{
	public:
		GLint maxRounds;
		GLint currentRound;
		GameObject* closestStone;
		GameObject* loserClosestStone;
		GLint player1Points;
		GLint player2Points;
		Vector3* buttonCenter;
		GLfloat houseDiameter; //House é a parte branca, até ao circulo azul
		GameLogic(GLint maxRounds,Vector3* buttonCenter, GLfloat houseDiameter);
		
		//Os pontos são ganhos pelo jogador com a pedra mais proxima do centro e sao iguais ao numero de pedras que tens dentro da house mais perto do centro que a pedra mais proxima inimiga
		//4 pedras por equipa
};

#endif