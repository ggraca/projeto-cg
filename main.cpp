#include "main.h"


GLint wSizeW = 800, wSizeH = 600;
GLfloat currentTime, lastTime,deltaTime;

Camera *cam;
vector<GameObject*> go_list;

GLuint  texture[2];
RgbImage imag;

void initWorld(){
	go_list.push_back((GameObject*)new Field(new Vector3(0, 0, 0)));
	go_list.push_back((GameObject*)new Stone(new Vector3(1, 0, 0)));
	go_list.push_back((GameObject*)new Stone(new Vector3(0, 0, 1)));
	go_list.push_back((GameObject*)new Stone(new Vector3(3, 0, 4)));

	Vector3 *obsPos = new Vector3(-2,2,-5);
	Vector3 *obsLookAt = new Vector3(0,20,0);
	GLfloat horizontalAngle =0;
	GLfloat verticalAngle =0;
	GLfloat mouseSpeed = 1;
	cam = new Camera(obsPos,obsLookAt,horizontalAngle,verticalAngle,wSizeW,wSizeH,mouseSpeed);


	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	imag.LoadBmpFile("data/ice1.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData()
	);
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//updateCameraDirection();
	glPushMatrix();
		glViewport (0,0,wSizeW, wSizeH);
		drawPerspective();

		//Observer
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		cam->update();
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
  glutPostRedisplay ();
}

void mouseListener(int x, int y){
	cam->updateAngleFPSCamera(x,y);
}

void arrowslistener(int key, int x, int y){
	cam->cameraArrows(key,x,y);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (wSizeW, wSizeH);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("OpenGL - Projeto");

	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	initWorld();


	glShadeModel(GL_SMOOTH);

	//glutFullScreen();

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(arrowslistener); 
	glutPassiveMotionFunc(mouseListener);

	glutMainLoop();
}
