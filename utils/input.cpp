#include "input.h"

void keyboard(unsigned char key, int x, int y){
    switch (key){
    	case '1':
    		if(glIsEnabled(GL_LIGHT0))
    			glDisable(GL_LIGHT0);
    		else
          glEnable(GL_LIGHT0);
    		break;
    	case '2':
    		if(glIsEnabled(GL_LIGHT1))
    			glDisable(GL_LIGHT1);
    		else
          glEnable(GL_LIGHT1);
    		break;
      case 32:                    //tecla SPACE
          if(game->readyToPlay)
            game->throwStone();
          break;
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
