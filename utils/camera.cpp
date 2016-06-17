#include "camera.h"


Camera::Camera(Vector3* a, Vector3* b){
  this->pos = a;
  this->dir = b;
}



void Camera::update(){
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
    pos->x, pos->y, pos->z,
    dir->x, dir->y, dir->z,
    0,1,0
  );
}
