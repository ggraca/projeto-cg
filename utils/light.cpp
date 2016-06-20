#include "light.h"


Light::Light(Vector3* pos, Vector3* lookAt, GLfloat cutoffAngle, GLfloat spotExp, GLenum light,GameObject* target,GLfloat *ambientLight, GLfloat *diffuseLight, GLfloat *specularLight) : GameObject(pos){
	this->lookAt=lookAt;
	this->light=light;
	
	this->ambientLight[0] = ambientLight[0]; 
	this->ambientLight[1] = ambientLight[1];
	this->ambientLight[2] = ambientLight[2];
	this->ambientLight[3] =ambientLight[3];
	this->diffuseLight[0] = diffuseLight[0];
	this->diffuseLight[1] = diffuseLight[1];
	this->diffuseLight[2] = diffuseLight[2];
	this->diffuseLight[3] = diffuseLight[3];
	this->specularLight[0] =specularLight[0];
	this->specularLight[1] = specularLight[1];
	this->specularLight[2] = specularLight[2];
	this->specularLight[3] = specularLight[3];
	
	this->cutoffAngle=cutoffAngle;
	this->spotExp=spotExp;
	this->target=target;
}

void Light::enable(){
	 glEnable(this->light);
}

void  Light::disable(){
	glDisable(this->light);
}
void Light::update(){
	
	if(target!=NULL){
		this->lookAt = target->pos;
	}
	// Assign created components to GL_LIGHT0
	glLightfv(light, GL_AMBIENT, this->ambientLight);
    glLightfv(light, GL_DIFFUSE, this->diffuseLight);
	glLightfv(light, GL_SPECULAR, this->specularLight);
    GLfloat pos[]= { this->pos->x,this->pos->y,this->pos->z,1.0f};
	glLightfv(light, GL_POSITION, pos);
	GLfloat dir[] = {this->lookAt->x-this->pos->x,this->lookAt->y-this->pos->y,this->lookAt->z-this->pos->z,1.0f};//{cam->dir->x,cam->dir->y,cam->dir->z};
	glLightfv(light, GL_SPOT_DIRECTION, dir);
	glLightf (light, GL_SPOT_EXPONENT ,spotExp);
	glLightf (light, GL_SPOT_CUTOFF, cutoffAngle);
}

void Light::defaultValues(){
	this->ambientLight[0] = 0.0f; 
	this->ambientLight[1] = 0.0f;
	this->ambientLight[2] = 0.0f;
	this->ambientLight[3] = 1.0f;
	this->diffuseLight[0] = 0.8f;
	this->diffuseLight[1] = 0.8f;
	this->diffuseLight[2] =  0.2f;
	this->diffuseLight[3] = 1.0f;
	this->specularLight[0] = 0.3f;
	this->specularLight[1] = 0.3f;
	this->specularLight[2] = 0.3f;
	this->specularLight[3] = 1.0f;
}

    