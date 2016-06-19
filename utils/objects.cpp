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
  glRotatef(-90, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);

  //Torus
  glColor3f(1.0, 0.0, 0.0);
  glutSolidTorus (0.5, 1, 20, 20);


  //Top
  int i, j, segments;
  float r;
  vector<Vector3*> coords;

  glColor3f(0.0, 0.0, 1.0);
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


void Field::draw(){
  //Base (45 * 5)
  GLint w = 5;
  GLint l = 45;
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
    glVertex3f(-w, 0, -l);
    glVertex3f(w, 0, -l);
    glVertex3f(w, 0, l);
    glVertex3f(-w, 0, l);
  glEnd();

  //Borders
  glColor3f(0.0, 0.0, 1.0);
  glPushMatrix();
    glTranslatef(0, 0, l);
    glRotatef(0, 0, 0, 0);
    this->drawBorder(w);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0, 0, -l);
    glRotatef(180, 0, 1, 0);
    this->drawBorder(w);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(w, 0, 0);
    glRotatef(90, 0, 1, 0);
    this->drawBorder(l);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-w, 0, 0);
    glRotatef(-90, 0, 1, 0);
    this->drawBorder(l);
  glPopMatrix();
}

void Field::drawBorder(GLint w){
  //Front
  glBegin(GL_QUADS);
    glVertex3f(-w, 0, 0);
    glVertex3f(w, 0, 0);
    glVertex3f(w, 1, 0.5);
    glVertex3f(-w, 1, 0.5);
  glEnd();

  //Back
  glBegin(GL_QUADS);
    glVertex3f(w, 1, 1);
    glVertex3f(-w, 1, 1);
    glVertex3f(-w, 0, 1);
    glVertex3f(w, 0, 1);
  glEnd();

  //Right
  glBegin(GL_QUADS);
    glVertex3f(w, 1, 0.5);
    glVertex3f(w, 1, 1);
    glVertex3f(w, 0, 1);
    glVertex3f(w, 0, 0);
  glEnd();

  //Left
  glBegin(GL_QUADS);
    glVertex3f(-w, 1, 1);
    glVertex3f(-w, 1, 0.5);
    glVertex3f(-w, 0, 0);
    glVertex3f(-w, 0, 1);
  glEnd();

  //Top
  glBegin(GL_QUADS);
    glVertex3f(-w, 1, 1);
    glVertex3f(w, 1, 1);
    glVertex3f(w, 1, 0.5);
    glVertex3f(-w, 1, 0.5);
  glEnd();

  /*
  //Bottom
  glBegin(GL_QUADS);
    glVertex3f(-w, 0, 1);
    glVertex3f(w, 0, 1);
    glVertex3f(w, 0, 0);
    glVertex3f(-w, 0, 0);
  glEnd();
  */
}
