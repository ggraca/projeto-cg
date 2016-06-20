#include "objects.h"


void Field::draw(){

  //Base (45 * 5)
  GLint w = 5;
  GLint l = 45;
  GLfloat wmin =-w;
  GLfloat wmax = w;
  GLfloat lmin =-l;
  GLfloat lmax = l;
  GLfloat malha = 0.2; //always par please

  float  specReflection[4] = {0.296648, 0.296648,0.296648, 1.0f }; //Pearl values
  float difReflection[4] = {1.0,0.829,0.22525,0.829};
  float ambientReflection[4] = {0.25 ,0.20725,0.20725,1.0};

  glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, difReflection);
  glMaterialfv(GL_FRONT, GL_AMBIENT, difReflection);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.088*128);


  glColor3f(1.0, 1.0, 1.0);

  //glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  float ti=0;
  for(float i= wmin; i<wmax;i+=malha){ //Ineficiente desenha 2 vezes o mesmo vertice mas yolo
    float tj = 0;
    for(float j= lmin; j<lmax;j+=malha){

      glBegin(GL_QUADS);
      	glNormal3f(0,1,0);  glTexCoord2f(ti, tj);  glVertex3f(i, 0, j);
      	glNormal3f(0,1,0);	glTexCoord2f(ti + malha, tj);  glVertex3f(i+malha, 0, j);
      	glNormal3f(0,1,0);	glTexCoord2f(ti + malha, tj + malha);  glVertex3f(i+malha, 0, j+malha);
      	glNormal3f(0,1,0);	glTexCoord2f(ti, tj + malha);  glVertex3f(i, 0, j+malha);
      glEnd();

      tj+=malha;
      if(tj > 1 - malha) tj -= 1 - malha;
    }
    ti+=malha;
    if(ti > 1 - malha) ti -= 1 - malha;
  }
  //glDisable(GL_TEXTURE_2D);


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

  //TO-DO definir aqui os componentes de luz dos circulos

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

Spectator::Spectator(Vector3* pos) : GameObject(pos){
  for(int i = 0; i < 3; i++)
    this->color[i] = rand()%3 / 2;
}

void Spectator::draw(){
  int i, j, segments = 20;
  vector<Vector3*> coords;

  glColor3f(this->color[0], this->color[1], this->color[2]);
  //Body
  glPushMatrix();
    glTranslatef(0, 1, 0);

    glBegin(GL_QUADS);
      glVertex3f(-1, 0, 0);
      glVertex3f(1, 0, 0);
      glVertex3f(1, -1, 0);
      glVertex3f(-1, -1, 0);
    glEnd();

    segments = 20;
    coords = gen_circle(1, segments);

    glBegin(GL_POLYGON);

    for(i = 0; i <= segments/2; i++)
      glVertex2f(coords[i]->x, coords[i]->y);

    glEnd();
  glPopMatrix();

  //Head
  glPushMatrix();
    glTranslatef(0, 2.4, 0);

    segments = 20;
    coords = gen_circle(0.5, segments);

    glBegin(GL_POLYGON);

      for(i = 0; i < segments; i++)
        glVertex2f(coords[i]->x, coords[i]->y);

    glEnd();
  glPopMatrix();
}
