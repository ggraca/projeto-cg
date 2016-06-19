#include "Testes.h"


GLint wSizeW, wSizeH,wPosX,wPosY;

GLfloat currentTime, lastTime,deltaTime;

Vector3 *camPos = new Vector3(0,0,0);

Camera *cam = new Camera(camPos,new Vector3(1,0,0),0,0,0,0,1);

GLfloat mouseSpeed = 1;

bool debug = false;

int initValues(){
	wPosX=0;
	wPosY=0;
	wSizeW=1920;
	wSizeH=1080;
	
	cam->updateWindowSize(wSizeW,wSizeH);
	cam->updateMouseSensitivity(mouseSpeed);
	
}


void drawPerspective(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble) wSizeW/wSizeH,1,100.0);
}


void drawGameObjects(){
	
	
	
}



void display(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	//updateCameraDirection();
	
	glPushMatrix();
		if(debug){
			glViewport (wSizeW/3,0,wSizeW, wSizeH); //Desenhar so parte do ecrã a outra parte é para a visão de cima
		}else glViewport (0,0,wSizeW, wSizeH);

		
		drawPerspective();
		
		//Observer
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		
		
		cam->drawCamera();
		drawGameObjects();
		
	
		
		
		
	glPopMatrix();
	
	if(debug){ //Visão de cima
		glPushMatrix();
			glViewport (0,0,wSizeW/3, wSizeH/3);
			//Perspective
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-16, 16, -16,16, -16,16);
			//Observer
			glMatrixMode( GL_MODELVIEW );
			glLoadIdentity();
			gluLookAt( 0,10,0, 0, 0, 0, 0.0, 0.0, -1.0 ); //observador: onde está, para onde olha e qual a direcção do up vector.
			
			
			drawGameObjects();
			
			
		glPopMatrix();
	}
	glutSwapBuffers();
	
}


void updateDeltaTime(){
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	
    deltaTime = float(currentTime - lastTime);	
}

void idle (void)
{
   //Corre sempre que o glut acabe de fazer calculos
	//cameraAngleUpdate();
	cam->update(camPos);
	
    glutPostRedisplay ();
}

void mouseListener(int x, int y){
	cam->updateAngleFPSCamera(x,y);
}

int main(int argc, char** argv){
	glutInit(&argc, argv); //===1:Inicia janela
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); //Double mode (duplo buffer), modelo RBG
	
	initValues();
	
	glutInitWindowSize (wSizeW, wSizeH);  //dimensoes (pixeis)
	glutInitWindowPosition (wPosX, wPosY); //localizacao da janela
	glutCreateWindow ("camera Tests");//criacao da janela
	
	glClear (GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	
	glutFullScreen();
	
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	//glutSpecialFunc(teclasNotAscii);
	glutPassiveMotionFunc(mouseListener); //Detectar movimento no rato sem butoes do rato premidos
	
	glutMainLoop();
}