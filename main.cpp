#include "main.h"


GLint wSizeW = 800, wSizeH = 600;
GLfloat currentTime, lastTime,deltaTime;

Camera *cam;
vector<GameObject*> go_list;

void initWorld(){
	go_list.push_back((GameObject*)new Stone(new Vector3(0, 0, 0)));

	Vector3 *obsPos = new Vector3(0,0,5);
	Vector3 *obsLookAt = new Vector3(3,0,3);
	GLfloat horizontalAngle =0;
	GLfloat verticalAngle =0;
	GLfloat mouseSpeed = 1;
	cam = new Camera(obsPos,obsLookAt,horizontalAngle,verticalAngle,wSizeW,wSizeH,mouseSpeed);
}


void drawPerspective(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble) wSizeW/wSizeH,1,100.0);
}


void drawScene(){

	/*
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
	*/

	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->update();

}



void display(){

	glClear(GL_COLOR_BUFFER_BIT);
	//updateCameraDirection();
	glPushMatrix();
		glViewport (0,0,wSizeW, wSizeH);
		drawPerspective();

		//Observer
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		cam->drawCamera();
		drawScene();
	glPopMatrix();

	/*
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

		drawScene();
	glPopMatrix();
	*/
	glutSwapBuffers();
}

void updateDeltaTime(){
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
  deltaTime = float(currentTime - lastTime);
}

void idle(){
	cam->update();
  glutPostRedisplay ();
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (wSizeW, wSizeH);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("OpenGL - Projeto");

	initWorld();

	//glClear (GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);

	//glutFullScreen();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutPassiveMotionFunc(mouseListener);

	glutMainLoop();
}
