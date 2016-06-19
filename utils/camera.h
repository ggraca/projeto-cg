#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include<GL/glu.h>
#include <GL/gl.h>
#endif


#include "utils.h"

#define PI		 3.14159
#define DEGREE_TO_RAD PI/180
#define RAD_TO_DEGREE 180/PI


using namespace std;

#ifndef CAMERA_H
#define CAMERA_H

class Camera{
	public:
		Camera(Vector3* pos, Vector3* dir, GLfloat hangle,GLfloat vangle,GLfloat windowW,GLfloat windowH, GLfloat msense);
		void update(Vector3* pos);
		void drawCamera();
		void updateAngleFPSCamera(int x, int y);
		void updateWindowSize(GLfloat wwidth, GLfloat wheight);
		void updateMouseSensitivity(GLfloat msense);
		GLfloat horizontalAngle, verticalAngle;
	private:
		Vector3* pos;
		Vector3* dir;
		Vector3* up;
		GLfloat width, height,mouseSensitivity,lastTime,currentTime,deltaTime;
		void updateUpVector();
		void updateDirection();

	
};
#endif /* CAMERA_H */

extern Camera * camera1;