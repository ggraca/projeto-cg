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

    Stone(Vector3* pos);

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
    void drawBorder(int width);
    void drawTarget();
};

class Spectator : GameObject{
  public:
    Spectator(Vector3* pos);
    void draw();
};


#endif //OBJECTS_H
