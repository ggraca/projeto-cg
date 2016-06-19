#include "gameobject.h"
#include "math.h"
#include <vector>

#ifndef OBJECTS_H
#define OBJECTS_H

class Stone : public GameObject{
  public:
    Vector3* mov;
    Vector3* ang_mov;
    float friction;

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
};


#endif //OBJECTS_H
