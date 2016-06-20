#include "objects.h"

Stone::Stone(Vector3* pos) : GameObject(pos){
  this->mov = new Vector3((rand()%100)*0.03, 0, (rand()%100)*0.03);
  this->ang_mov = new Vector3(0, -5, 0);
  this->friction = 0.01;
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

  if(this->mov->x < 0.001 && this->mov->x > -0.001){
    this->mov->x = 0;
    //printf("stop x\n");
  }
  if(this->mov->z < 0.001 && this->mov->z > -0.001){
    this->mov->z = 0;
    //printf("stop z\n");
  }
  if(this->ang_mov->y < 0.001 && this->ang_mov->y > -0.001)
    this->ang_mov->y = 0;
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


  for(int i = 0; i < (int)go_list.size(); i++){
    if(this != go_list[i] && typeid(*go_list[i]) == typeid(Stone)){
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
  glTranslatef(0, 0.15, 0);
  glRotatef(-90, 1, 0, 0);
  glScalef(this->radius, this->radius, this->radius);

  //Torus
  //Não funciona ainda pk torus não tem normais
  float specReflection[4] = {0.332741, 0.328634,0.346435, 1.0f }; //Obsidian values
  float difReflection[4] = {0.18275,0.17,0.22525,1.0};
  float ambientReflection[4] = {0.05375,0.05,0.06625,1.0};

  glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, difReflection);
  glMaterialfv(GL_FRONT, GL_AMBIENT, difReflection);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.3*128);

  glColor3f(1.0, 0.0, 0.0);
  glutSolidTorus (0.5, 1, 20, 20);


  //Top
  int i, j, segments;
  float r;
  vector<Vector3*> coords;


  specReflection[0] = 0.50196078; //Cyan plastic values
  specReflection[1] = 0.50196078;
  specReflection[3] = 0.50196078;

  difReflection[0] = 0.0;
  difReflection[1] = 0.50980392;
  difReflection[2] = 0.50980392;
  ambientReflection[0] = 0.0;
  ambientReflection[1] = 0.05;
  ambientReflection[2] = 0.06;
  glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, difReflection);
  glMaterialfv(GL_FRONT, GL_AMBIENT, difReflection);

  glMaterialf(GL_FRONT, GL_SHININESS, 0.25*128);
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

void Glass::drawPanel(int w){
  glPushMatrix();
    glTranslatef(0, 2, 0.5);

    glBegin(GL_QUADS);
      glVertex3f(-w - 0.5, 3, 0);
      glVertex3f(w + 0.5, 3, 0);
      glVertex3f(w + 0.5, 0, 0);
      glVertex3f(-w - 0.5, 0, 0);
    glEnd();

  glPopMatrix();
}

void Glass::lateDraw(){

  int l = 45 + 1, w = 5 + 1;

  glColor4f(0.4, 0.8, 0.95, 0.5);
  glPushMatrix();
    glTranslatef(0, 0, l);
    glRotatef(0, 0, 0, 0);
    this->drawPanel(w);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0, 0, -l);
    glRotatef(0, 0, 0, 0);
    this->drawPanel(w);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(w, 0, 0);
    glRotatef(90, 0, 1, 0);
    this->drawPanel(l);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-w, 0, 0);
    glRotatef(-90, 0, 1, 0);
    this->drawPanel(l);
  glPopMatrix();
}
