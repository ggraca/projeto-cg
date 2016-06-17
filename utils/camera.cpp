#include "camera.h"


Camera::Camera(Vector3* pos, Vector3* dir,Vector3* up){
  this->pos = pos;
  this->dir = dir;
  this->up = up;
}



void Camera::update(){
	this->pos = pos;
	this->dir = dir;
	this->up = up;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
    pos->x, pos->y, pos->z,
    dir->x, dir->y, dir->z,
    up->x,up->y,up->z
  );
}
