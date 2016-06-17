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

#include "camera.h"

using namespace std;

extern Camera *camera1;

void keyboard(unsigned char key, int x, int y);
