#include "objects.h"

using namespace std;

vector<Vector3*> gen_circle(float r, int segments){
  vector<Vector3*> coords;
  for(int i = 0; i < segments; i++){
    float theta = 2.0f * 3.1415926f * float(i) / float(segments);

    coords.push_back(new Vector3(
      r * cosf(theta),
      r * sinf(theta),
      0)
    );
  }

  return coords;
}

void Stone::draw(){
  //this->rot->x += 3;

  //Torus
  glColor4f(1.0, 0.0, 0.0, 0.5);
  glutSolidTorus (0.5, 1, 20, 20);


  //Top
  int i, j, segments;
  float r;
  vector<Vector3*> coords;

  glColor4f(0.0, 0.0, 1.0, 0.5);
  glPushMatrix();


    //Head
    r = 1.2;
    segments = 20;
    coords = gen_circle(r, segments);

    glTranslatef(0, 0, 0.5);
    glBegin(GL_POLYGON);

      for(int i = 0; i < segments; i++)
        glVertex2f(coords[i]->x, coords[i]->y);

    glEnd();


    //Grip1
    r = 0.2;
    segments = 10;
    coords = gen_circle(r, segments);

    glTranslatef(0, 0.4, 0);
    glBegin(GL_QUADS);

      for(i = 0; i < segments; i++){
        if(i == segments - 1) j = 0;
        else j = i + 1;

        glVertex3f(coords[i]->x, coords[i]->y, 0);
        glVertex3f(coords[i]->x, coords[i]->y + 0.6, 0.5);
        glVertex3f(coords[j]->x, coords[j]->y + 0.6, 0.5);
        glVertex3f(coords[j]->x, coords[j]->y, 0);
      }

		glEnd();


    //Grip2
    r = 0.1;
    segments = 10;
    coords = gen_circle(r, segments);

    glTranslatef(0, 0.6+r, 0.5);
    glRotatef(90, 1, 0, 0);

    glBegin(GL_QUADS);

      for(i = 0; i < segments; i++){
        if(i == segments - 1) j = 0;
        else j = i + 1;

        glVertex3f(coords[i]->x, coords[i]->y, 0);
        glVertex3f(coords[i]->x, coords[i]->y, 2);
        glVertex3f(coords[j]->x, coords[j]->y, 2);
        glVertex3f(coords[j]->x, coords[j]->y, 0);
      }

    glEnd();

  glPopMatrix();
}
