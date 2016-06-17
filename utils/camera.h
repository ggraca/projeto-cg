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

using namespace std;

#ifndef CAMERA_H
#define CAMERA_H

class Camera{
  public:
    Vector3* pos;
	Vector3* dir;
	Vector3* up;
	
	Camera(Vector3* pos, Vector3* dir,Vector3* up);
    void update();

	
};
#endif /* CAMERA_H */

extern Camera * camera1;