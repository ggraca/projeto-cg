#include "Testes.h"


GLint wSizeW, wSizeH,wPosX,wPosY;
GLfloat bule=0.5;
GLfloat bulePos[]= {3, 0, 3};
GLfloat quadPos[]= {4,0,4};
GLfloat currentTime, lastTime,deltaTime;

Vector3 *obsLookAt = new Vector3(3,0,3);
Vector3 *obsPos = new Vector3(0,0,0);
GLfloat mouseX, mouseY,lastMouseX,lastMouseY;
Camera *cam = new Camera(obsPos,obsLookAt,0,0,0,0,1);

GLfloat mouseSpeed = 1;
GLfloat horizontalAngle =0;
GLfloat verticalAngle =0;

int initValues(){
	wPosX=0;
	wPosY=0;
	wSizeW=1920;
	wSizeH=1080;
	mouseX = wSizeW/2;
	mouseY= wSizeH/2;
	
	cam->updateWindowSize(wSizeW,wSizeH);
	cam->updateMouseSensitivity(mouseSpeed);
	
}


void drawPerspective(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble) wSizeW/wSizeH,1,100.0);
}


void drawScene(){
	
	//Bule
	glPushMatrix();
		glTranslatef(bulePos[0], bulePos[1], bulePos[2]);
		glColor4f(LARANJA);//Definir previamente o LARANJA (#define LARANJA ?)
		glutSolidTeapot(bule);
	glPopMatrix();
	
	//Quadro
	glPushMatrix();
		GLfloat quad=3.0;
		glTranslatef(quadPos[0], quadPos[1], quadPos[2]);
		glColor4f(VERMELHO); //NOTA: Definir previamente o VERMELHO
		glBegin(GL_QUADS);
			glVertex3f( 0, 0, 0);
			glVertex3f(quad, 0, 0);
			glVertex3f(quad, quad, 0);
			glVertex3f(0, quad, 0);
		glEnd();
	glPopMatrix();
	
	drawAxis();
	
	//Camera
	glPushMatrix();
		glTranslatef(obsPos->x,obsPos->y,obsPos->z);
		glRotatef(0,horizontalAngle,0,0);
		glColor4f(1,1,1,1); //NOTA: Definir previamente o VERMELHO
		glBegin(GL_QUADS);
			glVertex3f( -1, 0, -1);
			glVertex3f(1, 0, -1);
			glVertex3f(1, 0, 1);
			glVertex3f(-1, 0, 1);
		glEnd();
	glPopMatrix();
	
	
}



void display(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	//updateCameraDirection();
	
	glPushMatrix();
		glViewport (wSizeW/3,0,wSizeW, wSizeH);
		
		drawPerspective();
		
		//Observer
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		
	
		cam->drawCamera();
		drawScene();
		
		
		
	glPopMatrix();
	
	glPushMatrix();
		glViewport (0,0,wSizeW/3, wSizeH/3);
		//Perspective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-16, 16, -16,16, -16,16);
		//Observer
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt( 0,10,0, 0, 0, 0, 0.0, 0.0, -1.0 ); //observador: onde est?, para onde olha e qual a direc??o do up vector.
		
		
		drawScene();
		
		
	glPopMatrix();
	
	glutSwapBuffers();
	
}
/*void teclasNotAscii(int key, int x, int y){
    if(key == GLUT_KEY_UP)
		obsPos[0]=obsPos[0]+incy; 
	if(key == GLUT_KEY_DOWN) 
		obsPos[2]=obsPos[2]-incy; 
	if(key == GLUT_KEY_LEFT)
		angulo=angulo+inca; 
	if(key == GLUT_KEY_RIGHT) 
		angulo=angulo-inca; 

	glutPostRedisplay();	
}*/






/*void cameraAngleUpdate(){

	// Compute new orientation
	horizontalAngle += mouseSpeed * (deltaTime/1000) * float(wSizeW/2 - mouseX );
	verticalAngle   += mouseSpeed * (deltaTime/1000) * float( wSizeH/2 - mouseY );
	// Reset mouse position for next frame

}*/

void updateDeltaTime(){
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	
    deltaTime = float(currentTime - lastTime);	
}

void idle (void)
{
   //Corre sempre que o glut acabe de fazer calculos
	//cameraAngleUpdate();
	cam->update();
	
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