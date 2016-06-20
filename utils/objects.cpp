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
  glTranslatef(0, 0.5, 0);
  glRotatef(-90, 1, 0, 0);
  glScalef(0.5, 0.5, 0.5);

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


void Field::draw(){

  //Base (45 * 5)
  GLint w = 5;
  GLint l = 45;
  
  float  specReflection[4] = {0.296648, 0.296648,0.296648, 1.0f }; //Pearl values
  float difReflection[4] = {1.0,0.829,0.22525,0.829};
  float ambientReflection[4] = {0.25 ,0.20725,0.20725,1.0};
  
  glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, difReflection);
  glMaterialfv(GL_FRONT, GL_AMBIENT, difReflection);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.088*128);
 
  
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
