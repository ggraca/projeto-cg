#include "main.h"

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z){
  this->x = x;
  this->y = y;
  this->z = z;
}

void Vector3::print(){
  printf("(%.2f, %.2f, %.2f)\n", x, y, z);
}
