#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include ""
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include<GL/glu.h>
#include <GL/gl.h>
#endif

#define LARANJA 0.5,1,0,1
#define VERMELHO 1,0,0,1
#define PI		 3.14159

GLint wSizeW, wSizeH,wPosX,wPosY;
GLfloat bule=0.5;
GLfloat bulePos[]= {3, 0, 3};
GLfloat quadPos[]= {4,0,4};
GLfloat obsUpVector[]={0,1,0};


GLfloat  obsPos[] = {0, 2, 0};
GLfloat obsLookAt[] = {3,0,3};

GLfloat mouseX, mouseY;

int initValues(){
	wPosX=0;
	wPosY=0;
	wSizeW=1920;
	wSizeH=1080;
	mouseX = wPosX/2;
	mouseY= wPosY/2;
}

GLfloat mouseSpeed = 1;
GLfloat horizontalAngle =0;
GLfloat verticalAngle =0;

GLfloat deltaTime;



void drawPerspective(){
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLdouble) wSizeW/wSizeH,1,100.0);
}


void drawScene(){
	
	//Bule
	glPushMatrix();
		glTranslatef(bulePos[0], bulePos[1], bulePos[2]);
		glColor4f(LARANJA);//Definir previamente o LARANJA (#define LARANJA …)
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
		glTranslatef(obsPos[0], obsPos[1], obsPos[2]);
		glRotatef(horizontalAngle,0,1,0);
		glColor4f(1,1,1,1); //NOTA: Definir previamente o VERMELHO
		glBegin(GL_QUADS);
			glVertex3f( -1, 0, -1);
			glVertex3f(1, 0, -1);
			glVertex3f(1, 0, 1);
			glVertex3f(-1, 0, 1);
		glEnd();
	glPopMatrix();
	
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

void display(){
	
	glClear(GL_COLOR_BUFFER_BIT);
	updateCameraDirection()
	
	glPushMatrix();
		glViewport (wSizeW/3,0,wSizeW, wSizeH);
		
		drawPerspective();
		
		//Observer
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		gluLookAt( obsPos[0],obsPos[1],obsPos[2], obsLookAt[0], obsLookAt[1], obsLookAt[2], obsUpVector[0],obsUpVector[1],obsUpVector[2] ); //observador: onde está, para onde olha e qual a direcção do up vector.
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
		gluLookAt( 0,10,0, 0, 0, 0, 0.0, 0.0, -1.0 ); //observador: onde está, para onde olha e qual a direcção do up vector.
		
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
void crossproduct(vector v1,vector v2,vector cross_p)

{

 cross_p.i = (v1.j*v2.k) - (v1.k*v2.j);

 cross_p.j = -((v1.i*v2.k) - (v1.k*v2.i));

 cross_p.k = (v1.i*v2.j) - (v1.j*v2.i);

 cout<<"crossproduct = "<<cross_p.i<<"i"<<cross_p.j<<"j"<<cross_p.k<<"k"<<endl;

}

void updateUpVector(){
	//Right vector * Direction vector = up vector
	// Right vector
	float right[]= {
    sin(horizontalAngle - 3.14f/2.0f),
    0,
    cos(horizontalAngle - 3.14f/2.0f)}
	
);
}
void updateCameraDirection()(
    obsLookAt[0] = cos(verticalAngle) * sin(horizontalAngle);
    obsLookAt[1] =sin(verticalAngle);
    obsLookAt[2] =cos(verticalAngle) * cos(horizontalAngle);
);
void updateMousePos(int x, int y){
	mouseX = x;
	mouseY = y
}

void fpsCameraUpdateValues(){

	// Compute new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - mouseX );
	verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - mouseY );
	// Reset mouse position for next frame
	updateMousePos(wSizeW/2, wSizeH/2);
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
	//glutSpecialFunc(teclasNotAscii);
	glutPassiveMotionFunc(updateMousePos); //Detectar movimento no rato sem butoes do rato premidos
	
	glutMainLoop();
}