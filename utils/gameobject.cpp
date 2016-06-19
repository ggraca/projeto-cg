#include "gameobject.h"

GameObject::GameObject(Vector3* a){
  this->pos = a;
  this->rot = new Vector3(0, 0, 0);
  this->mov = new Vector3(0, 0, 0);
  this->ang_mov = new Vector3(0, 0, 0);
  this->friction = 0.01;
}

void GameObject::add_child(GameObject* go){
  this->children.push_back(go);
}

void GameObject::update(){
  this->mov->x -= this->mov->x * this->friction;
  this->mov->y -= this->mov->y * this->friction;
  this->mov->z -= this->mov->z * this->friction;

  this->ang_mov->x -= this->ang_mov->x * this->friction;
  this->ang_mov->y -= this->ang_mov->y * this->friction;
  this->ang_mov->z -= this->ang_mov->z * this->friction;

  this->pos->x += this->mov->x * elapsedTime * 0.01;
  this->pos->y += this->mov->y * elapsedTime * 0.01;
  this->pos->z += this->mov->z * elapsedTime * 0.01;

  this->rot->x += this->ang_mov->x * elapsedTime * 0.01;
  this->rot->y += this->ang_mov->y * elapsedTime * 0.01;
  this->rot->z += this->ang_mov->z * elapsedTime * 0.01;

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
