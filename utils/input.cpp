#include "input.h"
#include "camera.h"

Camera * camera1;

void keyboard(unsigned char key, int x, int y){
    switch (key){

    case 'w':
        printf("w\n");
        //camera1->pos->z += 1;
        break;
    case 27:                    //tecla ESCAPE
        exit(0);
        break;
    }
}
