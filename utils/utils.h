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
		void print();
	};
#endif /* VECTOR3_H */