#include <stdio.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include<GL/glu.h>
#include <GL/gl.h>
#endif


using namespace std;

#ifndef VECTOR3_H
#define VECTOR3_H
	class Vector3{
	  public:
		GLfloat x, y, z;
		Vector3(GLfloat x, GLfloat y, GLfloat z);
		static Vector3* crossproduct(Vector3* v1, Vector3* v2);
		void print();
	};
#endif /* VECTOR3_H */

void drawText(char *string, Vector3 * v);

int drawAxis();