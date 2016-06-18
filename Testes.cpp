#include "Testes.h"
#include <string>

GLint wSizeW, wSizeH,wPosX,wPosY;
GLfloat bule=0.5;
GLfloat bulePos[]= {3, 0, 3};
GLfloat quadPos[]= {4,0,4};
GLfloat currentTime, lastTime,deltaTime;

GLfloat mouseX, mouseY,lastMouseX,lastMouseY;
Vector3 *obsUpVector = new Vector3(0,1,0);
Vector3 *obsLookAt = new Vector3(3,0,3);
Vector3 *obsPos = new Vector3(0,0,0);
Camera *cam = new Camera(obsPos,obsLookAt,obsUpVector);

int initValues(){
	wPosX=0;
	wPosY=0;
	wSizeW=1920;
	wSizeH=1080;
	mouseX = wSizeW/2;
	mouseY= wSizeH/2;
	currentTime = glutGet(GLUT_ELAPSED_TIME);

}

GLfloat mouseSpeed = 1;
GLfloat horizontalAngle =0;
GLfloat verticalAngle =0;

void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
	glColor4f(1,1,1,1); //NOTA: Definir previamente o VERMELHO
	glRasterPos3f(x,y,z);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void drawPerspective(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble) wSizeW/wSizeH,1,100.0);
}

int drawAxis(){
	glPushMatrix();
		glColor4f(1,0,0,1);
		glBegin(GL_LINES);
			glVertex3i( -100, 0, 0);
			glVertex3i(100, 0, 0);
		glEnd();
		glColor4f(0,1,0,1);
		glBegin(GL_LINES);
			glVertex3i(0,  -100, 0);
			glVertex3i(0, 100, 0);
		glEnd();
		glColor4f(0,0,1,1);
		glBegin(GL_LINES);
			glVertex3i( 0, 0, -100);
			glVertex3i( 0, 0,100);
		glEnd();
	glPopMatrix();
}

void drawScene(){

	//Bule
	glPushMatrix();
		glTranslatef(bulePos[0], bulePos[1], bulePos[2]);
		glColor4f(LARANJA);//Definir previamente o LARANJA (#define LARANJA �)
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



void updateCameraDirection(){

    obsLookAt->x = (GLfloat)(cos(verticalAngle*DEGREE_TO_RAD) * sin(horizontalAngle*DEGREE_TO_RAD));
    obsLookAt->y = (GLfloat)sin(verticalAngle*DEGREE_TO_RAD);
    obsLookAt->z = (GLfloat)(cos(verticalAngle*DEGREE_TO_RAD) * cos(horizontalAngle*DEGREE_TO_RAD));
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
		cam->pos=obsPos;
		cam->dir=obsLookAt;
		cam->up=obsUpVector;
		cam->update();

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
		gluLookAt( 0,10,0, 0, 0, 0, 0.0, 0.0, -1.0 ); //observador: onde est�, para onde olha e qual a direc��o do up vector.



		char texto[30];
		sprintf(texto, "Horizontal Angle = %.3f", horizontalAngle);
		desenhaTexto(texto,14, 0, 14);
		sprintf(texto, "Vertical Angle = %.3f", verticalAngle);
		desenhaTexto(texto,12,0,12);

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

Vector3 *crossproduct(Vector3* v1, Vector3* v2){

	Vector3* v3 = new Vector3(
					(v1->z*v2->y) - (v1->y*v2->z),
					(v1->x*v2->y) - (v1->y*v2->x),
					(v1->x*v2->z) - (v1->z*v2->x));

	return v3;
}

void updateUpVector(){
	//Right vector * Direction vector = up vector
	// Right vector
	Vector3 *obsRightVector = new Vector3(
									sin(horizontalAngle*DEGREE_TO_RAD - 3.14f/2.0f),
									0,
									cos(horizontalAngle*DEGREE_TO_RAD - 3.14f/2.0f));

	obsUpVector = crossproduct(obsRightVector, obsLookAt);
}

void updateMousePos(int x, int y){

	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

	float diffx=-(x-wSizeW/2); //check the difference between the current x and the last x position
	float diffy=-(y-wSizeH/2); //check the difference between the current y and the last y position

	verticalAngle += (float) diffy*mouseSpeed * (deltaTime/1000);; //set the xrot to xrot with the addition of the difference in the y position
	horizontalAngle += (float) diffx*mouseSpeed * (deltaTime/1000);;// set the xrot to yrot with the addition of the difference in the x position

	glutWarpPointer(wSizeW/2,wSizeH/2);
	just_warped = true;
}

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
    updateDeltaTime();
	//cameraAngleUpdate();
	updateCameraDirection();
    glutPostRedisplay ();
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
	glutPassiveMotionFunc(updateMousePos); //Detectar movimento no rato sem butoes do rato premidos

	glutMainLoop();
}
