#include <stdio.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <math.h>

#ifndef UTILS_H
#define UTILS_H

class Vector3{
  public:
		GLfloat x, y, z;
		Vector3(GLfloat x, GLfloat y, GLfloat z);
		static Vector3* crossproduct(Vector3* v1, Vector3* v2);
		static Vector3* normalizeVector(Vector3* v);
		void print();
	};

void drawText(char *string, Vector3* v);

void drawAxis();

extern GLuint texture[2];

#endif //UTILS_H
