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
  this->pos->x += this->mov->x * elapsedTime;
  this->pos->y += this->mov->y * elapsedTime;
  this->pos->z += this->mov->z * elapsedTime;
  printf("%f --- %f\n", this->mov->z, elapsedTime);

  glPushMatrix();

    glTranslatef(this->pos->x, this->pos->y, this->pos->z);
    glRotatef(rot->x, 1, 0, 0);
    glRotatef(rot->y, 0, 1, 0);
    glRotatef(rot->z, 0, 0, 1);

    for(int i = 0; i < (int)children.size(); i++)
      children[i]->update();

    this->draw();

  glPopMatrix();
}

void GameObject::draw(){
  glColor4f(1.0, 0.0, 0.0, 0.5);
  glutSolidTeapot (0.5);
}
