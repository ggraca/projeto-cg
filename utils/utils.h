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

    Vector3* operator*(float a);
    Vector3* operator+(float a);
    Vector3* operator-(float a);
    Vector3* operator=(Vector3* v);
    Vector3* operator*(Vector3* v);
    Vector3* operator+(Vector3* v);
    Vector3* operator-(Vector3* v);
    Vector3* operator+=(Vector3* v);
    Vector3* operator-=(Vector3* v);

    static Vector3* zero();
    void normalize();
		static Vector3* crossproduct(Vector3* v1, Vector3* v2);
		static Vector3* normalizeVector(Vector3* v);
		void print();
};

void drawText(char *string, Vector3* v);

void drawAxis();

extern GLuint texture[2];
extern float elapsedTime;

#endif //UTILS_H
