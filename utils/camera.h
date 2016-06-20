#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "utils.h"

#define PI		 3.14159
#define DEGREE_TO_RAD PI/180
#define RAD_TO_DEGREE 180/PI

#ifndef CAMERA_H
#define CAMERA_H

class Camera{
	public:
		Camera(Vector3* pos, Vector3* dir, GLfloat hangle, GLfloat vangle, GLfloat windowW, GLfloat windowH, GLfloat msense,GLfloat mspeed);
		void update();
		void drawCamera();
		void updateAngleFPSCamera(int x, int y);
		void updateWindowSize(GLfloat wwidth, GLfloat wheight);
		void updateMouseSensitivity(GLfloat msense);
		GLfloat horizontalAngle, verticalAngle;
		void cameraArrows(int key, int x, int y);
		void cameraAWSD(unsigned char key, int x, int y);
		void resetCamera();
		GLfloat deltaTime;
		Vector3 * pos;
		Vector3* dir;
	private:
		Vector3 *initialPos;
		Vector3 *initialDir;
		Vector3* up;
		Vector3 *obsRightVector;
		GLfloat width, height,mouseSensitivity,movespeed;
		void updateUpVector();
		void updateDirection();
		void updateMouseDeltaTime();
		void updateKeyboardDeltaTime();
};

extern Camera *cam;

#endif /* CAMERA_H */
