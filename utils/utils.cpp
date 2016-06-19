#include "utils.h"

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z){
  this->x = x;
  this->y = y;
  this->z = z;
}

void Vector3::print(){
  printf("(%.2f, %.2f, %.2f)\n", x, y, z);
}

Vector3*  Vector3::crossproduct(Vector3* v1, Vector3* v2){

	Vector3* v3 = new Vector3(
					(v1->y*v2->z) - (v1->z*v2->y),
					(v1->z*v2->x) - (v1->x*v2->z),
					(v1->x*v2->y) - (v1->y*v2->x));

	return v3;
}

Vector3* Vector3::normalizeVector(Vector3* v){
	GLfloat magnitude = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	
	Vector3 * result = new Vector3(v->x/magnitude,v->y/magnitude,v->z/magnitude);
	
	return result;
}

void drawText(char *string, Vector3 * v) 
{  
	glColor4f(1,1,1,1); //NOTA: Definir previamente o VERMELHO
	glRasterPos3f(v->x,v->y,v->z); 
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void drawAxis(){
	glPushMatrix();
		glColor4f(1,0,0,1); //X axis
		glBegin(GL_LINES);
			glVertex3i( -100, 0, 0);
			glVertex3i(100, 0, 0);
		glEnd();
		glColor4f(0,1,0,1);
		glBegin(GL_LINES);  //Y axis
			glVertex3i(0,  -100, 0);
			glVertex3i(0, 100, 0);
		glEnd();
		glColor4f(0,0,1,1);
		glBegin(GL_LINES);  //Z axis
			glVertex3i( 0, 0, -100);
			glVertex3i( 0, 0,100);
		glEnd();
	glPopMatrix();
}
