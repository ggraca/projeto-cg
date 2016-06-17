#include "main.h"

GameObject::GameObject(Vector3* a){
  this->pos = a;
}

void GameObject::draw(){
  GLfloat bule=0.5;

  glColor4f(1.0, 0.0, 0.0, 0.5);//Definir previamente o LARANJA (#define LARANJA ...)
  glPushMatrix();
    glTranslatef(this->pos->x, this->pos->y, this->pos->z);
    //glRotatef(90, 1, 0, 0);
    glutSolidTeapot (bule);
  glPopMatrix();
}

void GameObject::update(){

}
