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
#include "gameobject.h"
#include "camera.h"
#include "input.h"

#define LARANJA 0.5,1,0,1
#define VERMELHO 1,0,0,1
#define PI		 3.14159

using namespace std;