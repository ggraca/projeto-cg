#include "camera.h"

Camera::Camera(Vector3* pos, Vector3* dir, GLfloat hangle,GLfloat vangle,GLfloat windowW,GLfloat windowH, GLfloat msense){
  this->pos = pos;
  this->dir = dir;
  this->up = new Vector3(0,1,0);
  this->horizontalAngle=hangle;
  this->verticalAngle=vangle;
  this->width=windowW;
  this->height=windowH;
  this->mouseSensitivity= msense;
  this->lastTime = glutGet(GLUT_ELAPSED_TIME);
  this->deltaTime = 0;
}

void Camera::updateMouseSensitivity(GLfloat msense){
	this->mouseSensitivity= msense;
}

void Camera::updateWindowSize(GLfloat wwidth,GLfloat wheight){
	this->width=wwidth;
	this->height=wheight;
}

void Camera::updateDirection(){
	this->dir->x = (GLfloat)(cos(verticalAngle*DEGREE_TO_RAD) * sin(horizontalAngle*DEGREE_TO_RAD));
  this->dir->y = (GLfloat)sin(verticalAngle*DEGREE_TO_RAD);
  this->dir->z = (GLfloat)(cos(verticalAngle*DEGREE_TO_RAD) * cos(horizontalAngle*DEGREE_TO_RAD));

  this->dir = Vector3::normalizeVector(this->dir);
}

void Camera::updateUpVector(){
	//Right vector * Direction vector = up vector
	//Right vector
	Vector3 *obsRightVector = new Vector3(
  	sin(horizontalAngle*DEGREE_TO_RAD - 3.14f/2.0f),
    0,
  	cos(horizontalAngle*DEGREE_TO_RAD - 3.14f/2.0f)
  );

	obsRightVector = Vector3::normalizeVector(obsRightVector);

	this->up = Vector3::crossproduct(obsRightVector,this->dir);
}

void Camera::update(){
	updateDirection();
	updateUpVector();
}

void Camera::drawCamera(){
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			pos->x, pos->y, pos->z,
			pos->x+dir->x, pos->y+dir->y, pos->z+dir->z,
			up->x,up->y,up->z
		);
}

void Camera::cameraArrows(int key, int x, int y){
    if(key == GLUT_KEY_UP)
		this->verticalAngle += (float) mouseSensitivity*5;
	if(key == GLUT_KEY_DOWN)
		this->verticalAngle -= (float) mouseSensitivity*5;
	if(key == GLUT_KEY_LEFT)
		this->horizontalAngle += (float) mouseSensitivity*5; 
	if(key == GLUT_KEY_RIGHT)
		this->horizontalAngle -= (float) mouseSensitivity*5;  

}

void Camera::updateAngleFPSCamera(int x, int y){

	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

	float diffx=-(x-width/2); //check the difference between the current x and the last x position
	float diffy=-(y-height/2); //check the difference between the current y and the last y position

	lastTime = currentTime;
	currentTime = glutGet(GLUT_ELAPSED_TIME);

    deltaTime = float(currentTime - lastTime);


	this->verticalAngle += (float) diffy*mouseSensitivity * (deltaTime/1000);//set the xrot to xrot with the addition of the difference in the y position
	this->horizontalAngle += (float) diffx*mouseSensitivity * (deltaTime/1000);// set the xrot to yrot with the addition of the difference in the x position

	printf("Vert: %0.3f  Hor: %0.3f\n", verticalAngle, horizontalAngle);
	glutWarpPointer(width/2,height/2);
	just_warped = true;
}
