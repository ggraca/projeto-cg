#include "objects.h"

void Stone::draw(){
  this->rot->x += 3;

  //Torus
  glColor4f(1.0, 0.0, 0.0, 0.5);
  glPushMatrix();
    glutSolidTorus (0.5, 1, 20, 20);

    glColor4f(0.0, 0.0, 1.0, 0.5);
    glTranslatef(0, 0, 1);
    glBegin(GL_POLYGON);
      int num_segments = 20;
      int r = 2;
      for(int ii = 0; ii < num_segments; ii++){
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex3f(x, y, 0);//output vertex
      }
    glEnd();
  glPopMatrix();
}
