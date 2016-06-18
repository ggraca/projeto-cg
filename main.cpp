#include "main.h"


GLint wScreen=800, hScreen=600;
GLint max_fps = 30;
Camera *camera1;

vector<GameObject*> go_list;


void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);


    glViewport (0,0,wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
    gluPerspective(88.0, wScreen/hScreen, 0.1, 30);

    camera1->update();

    for(int i = 0; i < (int)go_list.size(); i++)
      go_list[i]->update();

    glutSwapBuffers();
}

void update(int value){
    glutPostRedisplay();
    glutTimerFunc(1000/max_fps,update, 1);
    //go_list[0]->pos->z += 0.05;
}

void initWorld(void){
  glClearColor(0.0, 0.0, 0.0, 0.0);
  //gluOrtho2D(-400, 400, -400, 400);
  glShadeModel(GL_FLAT);


  /*go_list.push_back(new GameObject(new Vector3(0, 0, 0)));
  GameObject* go = new GameObject(new Vector3(2, 0, 0));
  go->rot->x = 90;
  go_list[0]->add_child(go);
  */
  go_list.push_back((GameObject*)new Stone(new Vector3(0, 0, 0)));

  camera1 = new Camera(new Vector3(0.0,0.0,5.0), new Vector3(0.0, 0.0, 0.0), new Vector3(0, 1, 0));
}

int main(int argc, char **argv){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(wScreen,hScreen);
  glutCreateWindow("OpenGL - Projeto");

  initWorld();

  glutDisplayFunc(draw);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(1000/max_fps,update, 1);

  glutMainLoop();
}
