#include "gameobject.h"
#include "objects.h"
#include "math.h"
#include <vector>

#ifndef LIGHT_H
#define LIGHT_H

class Light : public GameObject{
  public:
    Light(Vector3* pos, Vector3* lookAt, GLfloat cutoffAngle, GLfloat spotExp, GLenum light,GameObject *target,GLfloat *ambientLight, GLfloat *diffuseLight, GLfloat *specularLight);
	Vector3* lookAt;
	GLfloat ambientLight[4],diffuseLight[4],specularLight[4], cutoffAngle, spotExp;
	GameObject *target;
    void update();
	void enable();
	void disable();
	void defaultValues();
  private:
	GLenum light;
};

#endif //LIGHT_H