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

Stone::Stone(Vector3* pos) : GameObject(pos){
  this->mov = new Vector3((rand()%100)*0.03, 0, (rand()%100)*0.03);
  this->ang_mov = new Vector3(0, -5, 0);
  this->friction = 0.00;
  this->radius = 0.25;
}

void Stone::earlyUpdate(){
  this->movement();
}

void Stone::update(){
  this->collision();
}

void Stone::movement(){
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
}

void Stone::collision(){
  //Field
  //TODO define field width and lenght somehow
  float r = this->radius;
  int w = 5, l = 45;


  if(this->pos->x + r > w || this->pos->x - r < -w){
    this->mov->x *= -1;
    this->movement();
  }
  if(this->pos->z + r > l || this->pos->z - r < -l){
    this->mov->z *= -1;
    this->movement();
  }

  //TODO verify object type
  for(int i = 1; i < (int)go_list.size(); i++){
    if(this != go_list[i]){
      Stone* s = (Stone*)go_list[i];

      float dx = abs(this->pos->x - s->pos->x);
      float dz = abs(this->pos->z - s->pos->z);

      if(dx < r && dz < r){

        float tx = s->mov->x;
        float tz = s->mov->z;

        s->mov->x = this->mov->x;
        s->mov->z = this->mov->z;

        this->mov->x = tx;
        this->mov->z = tz;

        s->movement();
      }
    }
  }
}

void Stone::draw(){
  glTranslatef(0, 0.5, 0);
  glRotatef(-90, 1, 0, 0);
  glScalef(this->radius, this->radius, this->radius);

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
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-w, 0, -l);
    glTexCoord2f(w, 0); glVertex3f(w, 0, -l);
    glTexCoord2f(w, l); glVertex3f(w, 0, l);
    glTexCoord2f(0, l); glVertex3f(-w, 0, l);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  //Circles
  glPushMatrix();
    glTranslatef(0, 0, 40);
    drawTarget();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0, 0, -40);
    drawTarget();
  glPopMatrix();

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

void Field::drawTarget(){
  int i, j, segments = 20;
  vector<Vector3*> inner, outer;

  inner = gen_circle(0.5, segments);
  outer = gen_circle(1.5, segments);

  glColor3f(1, 0, 0);
  glBegin(GL_QUADS);
    for(i = 0; i < segments; i++){
      if(i == segments - 1) j = 0;
      else j = i + 1;

      glVertex3f(outer[i]->x, 0.01, outer[i]->y);
      glVertex3f(outer[j]->x, 0.01, outer[j]->y);
      glVertex3f(inner[j]->x, 0.01, inner[j]->y);
      glVertex3f(inner[i]->x, 0.01, inner[i]->y);
    }
  glEnd();

  inner = gen_circle(2.5, segments);
  outer = gen_circle(3.5, segments);

  glColor3f(0, 0, 1);
  glBegin(GL_QUADS);
    for(i = 0; i < segments; i++){
      if(i == segments - 1) j = 0;
      else j = i + 1;

      glVertex3f(outer[i]->x, 0.01, outer[i]->y);
      glVertex3f(outer[j]->x, 0.01, outer[j]->y);
      glVertex3f(inner[j]->x, 0.01, inner[j]->y);
      glVertex3f(inner[i]->x, 0.01, inner[i]->y);
    }
  glEnd();
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
