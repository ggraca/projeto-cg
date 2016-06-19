#include "main.h"


GLint wSizeW = 800, wSizeH = 600;
GLfloat currentTime, lastTime, deltaTime;

int maxFps = 30;
float elapsedTime = 0, previousTime = 0;

Camera *cam;
vector<GameObject*> go_list;

GLuint  texture[2];
RgbImage imag;

void initWorld(){

	go_list.push_back((GameObject*)new Field(new Vector3(0, 0, 0)));
	go_list.push_back((GameObject*)new Stone(new Vector3(1, 0, 0)));
	go_list.push_back((GameObject*)new Stone(new Vector3(0, 0, 1)));

	Stone* test = new Stone(new Vector3(3, 0, 4));
	go_list.push_back((GameObject*)test);

	Vector3 *obsPos = new Vector3(30,30,0);
	Vector3 *obsLookAt = new Vector3(0,0,0);
	GLfloat horizontalAngle =0;
	GLfloat verticalAngle =0;
	GLfloat mouseSpeed = 3;
	GLfloat moveSpeed = 6;
	cam = new Camera(obsPos,obsLookAt,horizontalAngle,verticalAngle,wSizeW,wSizeH,mouseSpeed,moveSpeed);

	//-------------------------------------------------------------------

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

	//-------------------------------------------------------------------
}


void drawPerspective(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble) wSizeW/wSizeH,1,100.0);
}


void drawScene(){
	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->earlyUpdate_();
	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->update_();
	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->draw_();
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

	glutSwapBuffers();
}

void update(int v){
	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = float(currentTime - lastTime);

	/*if(elapsedTime < 1000/maxFps)
		sleep(1000/maxFps - elapsedTime);
	*/
	
	cam->deltaTime = elapsedTime/1000;
	
	glutPostRedisplay();
	glutTimerFunc(1000/maxFps,update, 1);
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

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (wSizeW, wSizeH);
	glutInitWindowPosition (0, 0);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); 
	
	glutCreateWindow ("OpenGL - Projeto");
	
	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glShadeModel(GL_SMOOTH);

	initWorld();

	//glutFullScreen();

	glutDisplayFunc(display);
	glutSpecialFunc(arrowsListener);
	glutKeyboardFunc(keyboardListener);

	glutPassiveMotionFunc(mouseListener);
	glutTimerFunc(1000/maxFps, update, 1);

	glutMainLoop();
}
