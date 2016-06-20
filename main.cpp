#include "main.h"

GLint wSizeW = 800, wSizeH = 600;

int maxFps = 60;
float elapsedTime = 0, previousTime = 0;

Camera *cam;
GLuint  texture[2];
vector<GameObject*> go_list;
Field *field;
GameLogic* game;
Light* lightClosest;
Light* lightCurrent[2];



void init(){
	srand (time(NULL));

	//TODO create loadtextures()
	RgbImage imag;

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

	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	imag.LoadBmpFile("data/pub.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData()
	);
}

void initWorld(){
	//Field
	field = new Field(new Vector3(0, 0, 0));

	//Spectators
	Spectator* s;
	for(int i = -44; i <= 44; i += 3){

		s = new Spectator(new Vector3(7.5, 3, i));
		s->rot->y = 90;
		go_list.push_back((GameObject*)s);

		s = new Spectator(new Vector3(-7.5, 3, i));
		s->rot->y = 90;
		go_list.push_back((GameObject*)s);
	}

	go_list.push_back((GameObject*)new Glass(new Vector3(0, 1, 0)));


	//Stones
	Stone* test = new Stone(new Vector3(1, 0, -10),2);
	go_list.push_back((GameObject*)test);

	//Camera
	Vector3 *obsPos = new Vector3(0,5,-10);
	Vector3 *obsLookAt = new Vector3(0,0,0);
	GLfloat horizontalAngle =0;
	GLfloat verticalAngle =0;
	GLfloat mouseSpeed = 3;
	GLfloat moveSpeed = 40;
	cam = new Camera(obsPos,obsLookAt,horizontalAngle,verticalAngle,wSizeW,wSizeH,mouseSpeed,moveSpeed);

	//Ambient light
	GLfloat color[]={0.5f,0.5f,0.5f,1.0f};
	go_list.push_back((GameObject*) new Light(new Vector3( 0,1000,0),new Vector3(0,1001,0), 0.0f, 0.0f, true, (GLenum) GL_LIGHT1,NULL,color,color,color));
	((Light*)(go_list[go_list.size()-1]))->enable();

	//Spot lights
	GLfloat ambient[]={ 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat diffuse[]= { 0.8f, 0.8f, 0.2, 1.0f };
	GLfloat specular[]= { 0.3f, 0.3f, 0.3f, 1.0f };

	lightCurrent[0] = new Light(new Vector3( -7,15,20),new Vector3(0,0,0), 5.0f, 100.0f, false, (GLenum) GL_LIGHT0,NULL,ambient,diffuse,specular);
	go_list.push_back((GameObject*) lightCurrent[0]);
	lightCurrent[1] = new Light(new Vector3( 7,15,20),new Vector3(0,0,0), 5.0f, 100.0f, false, (GLenum) GL_LIGHT3,NULL,ambient,diffuse,specular);
	go_list.push_back((GameObject*) lightCurrent[1]);

	GLfloat diffuse1[]= { 0.2f, 0.8f, 0.4f, 1.0f };
	GLfloat specular1[]= { 0.3f, 0.3f, 0.3f, 1.0f };

	lightClosest = new Light(new Vector3( 0,15,40),new Vector3(0,0,0), 5.0f, 100.0f, false, (GLenum) GL_LIGHT2,NULL,ambient,diffuse1,specular1);
	go_list.push_back((GameObject*) lightClosest);



	game = new GameLogic();
	game->startRound();
}

void drawScene(){

	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->earlyUpdate_();
	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->update_();
	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->draw_();

	field->drawWithReflections(go_list);

	for(int i = 0; i < (int)go_list.size(); i++)
		go_list[i]->lateDraw_();

	game->update();

	Stone* s = game->getClosestStone();
	if(s != NULL){
		lightClosest->target = (GameObject*)s;
		lightClosest->enable();
	}
	else{
		lightClosest->target = NULL;
		lightClosest->disable();
	}

	//
	s = game->currentStone;
	if(s != NULL){
		lightCurrent[0]->target = (GameObject*)s;
		lightCurrent[0]->enable();
		lightCurrent[1]->target = (GameObject*)s;
		lightCurrent[1]->enable();
	}
	else{
		lightCurrent[0]->target = NULL;
		lightCurrent[0]->disable();
		lightCurrent[1]->target = NULL;
		lightCurrent[1]->disable();
	}


}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |  GL_STENCIL_BUFFER_BIT);
	glPushMatrix();
		glViewport (0,0,wSizeW, wSizeH);

		//Prespective
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(65.0, (GLdouble) wSizeW/wSizeH,1,100.0);

		//Observer
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		cam->update();
		cam->drawCamera();

		drawScene();

	glPopMatrix();
	glutSwapBuffers();
}

void update(int v){
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = float(currentTime - previousTime);
	previousTime = currentTime;

	/*if(elapsedTime < 1000/maxFps)
		sleep(1000/maxFps - elapsedTime);
	*/

	cam->deltaTime = elapsedTime/1000;

	glutPostRedisplay();
	glutTimerFunc(1000/maxFps,update, 1);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_STENCIL_BUFFER_BIT);
	glutInitWindowSize (wSizeW, wSizeH);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("OpenGL - Projeto");

	//Luz
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);


	//glFrontFace(GL_CW);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//Luz-Fim

	//Reflection
	glEnable(GL_STENCIL_TEST);
	//Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	glDepthMask(GL_TRUE);


	init();
	initWorld();

	glutDisplayFunc(display);
	glutSpecialFunc(arrowsListener);
	glutKeyboardFunc(keyboardListener);
	glutPassiveMotionFunc(mouseListener);
	glutTimerFunc(1000/maxFps, update, 1);

	glutMainLoop();
}
