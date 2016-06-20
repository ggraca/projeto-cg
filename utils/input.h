#include <stdio.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "camera.h"

#ifndef INPUT_H
#define INPUT_H

void keyboard(unsigned char key, int x, int y);
void mouseListener(int x, int y);
void arrowsListener(int key, int x, int y);
void keyboardListener(unsigned char key, int x, int y);

#endif //INPUT_H
