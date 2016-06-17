#include "gameobject.h"

GameObject::GameObject(Vector3* a){
  this->pos = a;
  this->rot = new Vector3(0, 0, 0);
  this->mov = new Vector3(0, 0, 0);
  this->ang_mov = new Vector3(0, 0, 0);
}

void GameObject::add_child(GameObject* go){
  this->children.push_back(go);
}

void GameObject::update(){
  glPushMatrix();
    glRotatef(rot->x, 1, 0, 0);
    glRotatef(rot->y, 0, 1, 0);
    glRotatef(rot->z, 0, 0, 1);

    glTranslatef(this->pos->x, this->pos->y, this->pos->z);

    for(int i = 0; i < (int)children.size(); i++)
      children[i]->update();

    this->draw();
  glPopMatrix();
}

void GameObject::draw(){
  glColor4f(1.0, 0.0, 0.0, 0.5);
  glutSolidTorus (0.5, 1, 20, 20);
  //glutSolidTeapot (bule);
}
