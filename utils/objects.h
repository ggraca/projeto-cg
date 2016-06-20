#include "gameobject.h"
#include "math.h"
#include <vector>
#include <typeinfo>

using namespace std;

#ifndef OBJECTS_H
#define OBJECTS_H

class Stone : public GameObject{
  public:
    Vector3* mov;
    Vector3* ang_mov;
    float friction;
    float radius;
	GLfloat color[3];
	int player;

    Stone(Vector3* pos, int player);

    void draw();
    void earlyUpdate();
    void update();
    void movement();
    void collision();
};

class Field : GameObject{
  public:
    Field(Vector3* pos) : GameObject(pos){};
    void draw();
    void drawTarget();
    void drawBorder(int width);
    void drawStair(int width, int n);
	void drawWithReflections(vector<GameObject*> go_old);
};

class Glass : public GameObject{
  public:
    Glass(Vector3* pos) : GameObject(pos){};
    void lateDraw();
    void drawPanel(int w);
};

class Spectator : public GameObject{
  public:
    float color[3];
    Spectator(Vector3* pos);
    void draw();
};

class Lamp : public GameObject{
  public:
    Lamp(Vector3* pos);
    void draw();
};

#endif //OBJECTS_H
