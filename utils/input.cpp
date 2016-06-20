#include "input.h"

void keyboard(unsigned char key, int x, int y){
    switch (key){
    case 27:                    //tecla ESCAPE
        exit(0);
        break;
    }
}

void mouseListener(int x, int y){
	cam->updateAngleFPSCamera(x,y);
}

void arrowsListener(int key, int x, int y){
	cam->cameraArrows(key,x,y);
}

void keyboardListener(unsigned char key, int x, int y){
	cam->cameraAWSD( key,  x,  y);
	keyboard(key,x,y);
}
