#include "gameobject.h"
#include "math.h"
#include <vector>

#ifndef OBJECTS_H
#define OBJECTS_H

class Stone : GameObject{
  public:
    Stone(Vector3* pos) : GameObject(pos){};
    void draw();
};

class Teapot : GameObject{
  public:
    Teapot(Vector3* pos) : GameObject(pos){};
    void draw();
};

class Field : GameObject{
  public:
    Field(Vector3* pos) : GameObject(pos){};
    void draw();
    void drawBorder(int width);
};


#endif //OBJECTS_H
