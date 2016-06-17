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

class GameObject{
  public:
    Vector3* pos;
    Vector3* rot;
    Vector3* mov;
    Vector3* ang_mov;
    vector<GameObject*> children;

    GameObject(Vector3* a);
    void update();
    void draw();
    void add_child(GameObject* go);
};
