#include "objects.h"

GLfloat reflectionAlpha =1.0f;

void Field::draw(){

  //Base (45 * 5)
  GLint w = 5;
  GLint l = 45;
  GLfloat wmin =-w;
  GLfloat wmax = w;
  GLfloat lmin =-l;
  GLfloat lmax = l;
  GLfloat malha = 0.1; //always par please
  GLfloat textwinc = 1/((w*2)/malha);
  GLfloat textlinc = 1/((l*2)/malha);
  float  specReflection[4] = {0.296648, 0.296648,0.296648, 1.0f }; //Pearl values
  float difReflection[4] = {0.829,0.22525,0.829, 1.0f};
  float ambientReflection[4] = {0.25 ,0.20725,0.20725,1.0};

  glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, difReflection);
  glMaterialfv(GL_FRONT, GL_AMBIENT, difReflection);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.088*128);


  glColor4f(1.0, 1.0, 1.0,reflectionAlpha);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[0]);
  
  float ti=0;
  for(float i= wmin; i<wmax;i+=malha){ //Ineficiente desenha 2 vezes o mesmo vertice mas yolo
    float tj = 0;
    for(float j= lmin; j<lmax;j+=malha){
      glBegin(GL_QUADS);
      	glNormal3f(0,1,0);  glTexCoord2f(ti, tj);  glVertex3f(i, 0, j);
      	glNormal3f(0,1,0);	glTexCoord2f(ti + textlinc, tj);  glVertex3f(i+malha, 0, j);
      	glNormal3f(0,1,0);	glTexCoord2f(ti + textlinc, tj + textwinc);  glVertex3f(i+malha, 0, j+malha);
      	glNormal3f(0,1,0);	glTexCoord2f(ti, tj + textwinc);  glVertex3f(i, 0, j+malha);
      glEnd();

      tj+=textlinc;
      if(tj > 1 - textlinc) tj = 1;
    }
    ti+=textwinc;
    if(ti > 1 - textwinc) ti = 1;
  }
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
  glPushMatrix();
    glTranslatef(0, 0, l);
    glRotatef(0, 0, 0, 0);
    this->drawBorder(w+1);
    this->drawStair(w+1, 2);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0, 0, -l);
    glRotatef(180, 0, 1, 0);
    this->drawBorder(w+1);
    this->drawStair(w+1, 2);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(w, 0, 0);
    glRotatef(90, 0, 1, 0);
    this->drawBorder(l+1);
    this->drawStair(l+1, 2);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-w, 0, 0);
    glRotatef(-90, 0, 1, 0);
    this->drawBorder(l+1);
    this->drawStair(l+1, 2);
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

void Field::drawBorder(int w){
  glColor3f(1.0, 1.0, 1.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,texture[1]);
  /*
  //Front
  glBegin(GL_QUADS);
    glTexCoord3f(w/2, 1, 1); glVertex3f(-w, 1, 1);
    glTexCoord3f(0, 1, 1); glVertex3f(w, 1, 1);
    glTexCoord3f(0, 0, 0); glVertex3f(w, 0, 0);
    glTexCoord3f(w/2, 0, 0); glVertex3f(-w, 0, 0);
  glEnd();
*/

  float l = sqrt(2);
  glPushMatrix();
    glTranslatef(0, 0.5, 0.5);
    glRotatef(45, 1, 0, 0);
    drawMesh(0.2, w, l/2, 500/97, l);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void Field::drawStair(int w, int n){
  glColor3f(0.5, 0.5, 0.5);

  glTranslatef(0, 1, 1);
  for(int i = 0; i < n; i++){

    glBegin(GL_QUADS);
      glVertex3f(-w, 2, 0);
      glVertex3f(w, 2, 0);
      glVertex3f(w, 0, 0);
      glVertex3f(-w, 0, 0);
    glEnd();

    w+=3;
    glBegin(GL_QUADS);
      glVertex3f(-w, 2, 3);
      glVertex3f(w, 2, 3);
      glVertex3f(w, 2, 0);
      glVertex3f(-w, 2, 0);
    glEnd();

    glTranslatef(0, 2, 3);
  }
}

Spectator::Spectator(Vector3* pos) : GameObject(pos){
  for(int i = 0; i < 3; i++)
    this->color[i] = rand()%3 / 2;
}

void Spectator::draw(){
  int i, segments = 20;
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

void Field::drawWithReflections(vector<GameObject*> go_list){
	//REFLEXÃO 
	glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer
	glColorMask(0, 0, 0, 0); //Nao escreve no color buffer
	glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade
	glStencilFunc(GL_ALWAYS, 1, 1); //O
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //
	//Coloca a 1 todos os pixels no stencil buffer que representam o chão
	draw_();
	
	glColorMask(1, 1, 1, 1); //Activa a escrita de cor
	glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade
	
	glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
	
	//Desenha o objecto com uma reflexão vertical ond stencil buffer é 1
	for(int i = 0; i < (int)go_list.size(); i++){
		glPushMatrix();
			glScalef(1, -1, 1);
			go_list[i]->draw_();
		glPopMatrix();
	}
	
	glDisable(GL_STENCIL_TEST); //Desactiva a utilização do stencil buffer
	
    //Blending (para transparência)
	glPushMatrix();
		glEnable(GL_BLEND);
		reflectionAlpha = 0.9;
		draw();
		glDisable(GL_BLEND);
	glPopMatrix();
	reflectionAlpha = 1.0f;
	//FIM REFLEXÃO
	
}
