#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/glut.h>
#include <vector>
#include <math.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "utils\gameobject.h"
#include "utils\camera.h"
#include "utils\input.h"

#define LARANJA 0.5,1,0,1
#define VERMELHO 1,0,0,1
#define PI		 3.14159
#define DEGREE_TO_RAD PI/180
#define RAD_TO_DEGREE 180/PI

using namespace std;