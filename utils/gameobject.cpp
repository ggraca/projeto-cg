#include "gameobject.h"

GameObject::GameObject(Vector3* a){
  this->pos = a;
  this->rot = new Vector3(0, 0, 0);
}

void GameObject::add_child(GameObject* go){
  this->children.push_back(go);
}

void GameObject::earlyUpdate_(){
  for(int i = 0; i < (int)children.size(); i++)
    children[i]->earlyUpdate();
  this->earlyUpdate();
}

void GameObject::update_(){
  for(int i = 0; i < (int)children.size(); i++)
  children[i]->update();
  this->update();
}

void GameObject::draw_(){
  glPushMatrix();
    glTranslatef(this->pos->x, this->pos->y, this->pos->z);
    glRotatef(rot->x, 1, 0, 0);
    glRotatef(rot->y, 0, 1, 0);
    glRotatef(rot->z, 0, 0, 1);

    for(int i = 0; i < (int)children.size(); i++)
      children[i]->draw();

    this->draw();

  glPopMatrix();
}
