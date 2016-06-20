#include "utils.h"

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z){
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3* Vector3::zero(){
  return new Vector3(0, 0, 0);
}

Vector3* Vector3::operator*(float a){
  return new Vector3(this->x * a, this->y * a, this->z * a);
}

Vector3* Vector3::operator+(float a){
  return new Vector3(this->x + a, this->y + a, this->z + a);
}

Vector3* Vector3::operator-(float a){
  return new Vector3(this->x - a, this->y - a, this->z - a);
}

Vector3* Vector3::operator=(Vector3* v){
  this->x = v->x;
  this->y = v->y;
  this->z = v->z;
  return this;
}

Vector3* Vector3::operator*(Vector3* v){
  return new Vector3(
		(this->y*v->z) - (this->z*v->y),
		(this->z*v->x) - (this->x*v->z),
		(this->x*v->y) - (this->y*v->x)
  );
}

Vector3* Vector3::operator+(Vector3* v){
  return new Vector3(this->x + v->x, this->y + v->y, this->z + v->z);
}

Vector3* Vector3::operator-(Vector3* v){
  return new Vector3(this->x - v->x, this->y - v->y, this->z - v->z);
}

Vector3* Vector3::operator+=(Vector3* v){
  (*this) = (*this) + v;
  return this;
}

Vector3* Vector3::operator-=(Vector3* v){
  (*this) = (*this) - v;
  return this;
}

void Vector3::normalize(){
  GLfloat magnitude = sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	this->x /= magnitude;
  this->y /= magnitude;
  this->z /= magnitude;
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

