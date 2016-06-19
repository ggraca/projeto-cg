#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <stdio.h>
#include <vector>

#include "utils.h"
using namespace std;

//-----------------------------------------------------

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject{
  public:
    Vector3* pos;
    Vector3* rot;
    vector<GameObject*> children;

    GameObject(Vector3* a);
    void add_child(GameObject* go);

    void earlyUpdate_();
    void update_();
    void draw_();

    virtual void earlyUpdate(){};
    virtual void update(){};
    virtual void draw(){};
};


#endif //GAMEOBJECT_H
