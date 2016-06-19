#include <stdio.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#ifndef UTILS_H
#define UTILS_H

class Vector3{
  public:
		GLfloat x, y, z;
		Vector3(GLfloat x, GLfloat y, GLfloat z);
		static Vector3* crossproduct(Vector3* v1, Vector3* v2);
		void print();
	};

void drawText(char *string, Vector3 * v);

void drawAxis();

#endif //UTILS_H
