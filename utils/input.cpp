#include "input.h"

void keyboard(unsigned char key, int x, int y){
    switch (key){

    case 'w':
        printf("w\n");
        break;
    case 27:                    //tecla ESCAPE
        exit(0);
        break;
    }
}

void mouseListener(int x, int y){
	cam->updateAngleFPSCamera(x,y);
}
