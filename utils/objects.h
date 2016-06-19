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

#endif //OBJECTS_H
