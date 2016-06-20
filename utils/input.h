#include <stdio.h>
#include "camera.h"
#include "gamelogic.h"

#ifndef INPUT_H
#define INPUT_H

void keyboard(unsigned char key, int x, int y);
void mouseListener(int x, int y);
void arrowsListener(int key, int x, int y);
void keyboardListener(unsigned char key, int x, int y);

#endif //INPUT_H
