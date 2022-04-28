#include <GL/glut.h>

double rotate_x = 0;
double rotate_y = 0;

void init(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);
	  glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h){
  float aspect = (float)w / (float)h;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, aspect, 0.1, 500.0);
  
  glMatrixMode(GL_MODELVIEW);
}

void drawCube(){
  float size = 1.0;

  glBegin(GL_QUADS);
  // front face
  glColor3f(1.0,0.0,0.0);
  glVertex3f(size/2,size/2,size/2);
  glVertex3f(-size/2,size/2,size/2);
  glVertex3f(-size/2,-size/2,size/2);
  glVertex3f(size/2,-size/2,size/2);
  // left face
  glColor3f(0.0,0.0,1.0);
  glVertex3f(-size/2,size/2,size/2);
  glVertex3f(-size/2,-size/2,size/2);
  glVertex3f(-size/2,-size/2,-size/2);
  glVertex3f(-size/2,size/2,-size/2);
  // back face
  glColor3f(1.0, 0.5, 0.0);
  glVertex3f(size/2,size/2,-size/2);
  glVertex3f(-size/2,size/2,-size/2);
  glVertex3f(-size/2,-size/2,-size/2);
  glVertex3f(size/2,-size/2,-size/2);
  // right face
  glColor3f(0.0,1.0,0.0);
  glVertex3f(size/2,size/2,size/2);
  glVertex3f(size/2,-size/2,size/2);
  glVertex3f(size/2,-size/2,-size/2);
  glVertex3f(size/2,size/2,-size/2);
  // top face
  glColor3f(1.0,1.0,0.0);
  glVertex3f(size/2,size/2,size/2);
  glVertex3f(-size/2,size/2,size/2);
  glVertex3f(-size/2,size/2,-size/2);
  glVertex3f(size/2,size/2,-size/2);
  // bottom face
  glColor3f(1.0,1.0,1.0);
  glVertex3f(size/2,-size/2,size/2);
  glVertex3f(-size/2,-size/2,size/2);
  glVertex3f(-size/2,-size/2,-size/2);
  glVertex3f(size/2,-size/2,-size/2);
  glEnd();

}

void draw(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslated(0.0, 0.0, -5.0);

  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );

  drawCube();

  glutSwapBuffers();
} 



void specialKeys( int key, int x, int y ) {
 
  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
  //  Request display update
  glutPostRedisplay();
 
}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(1080,720);
    glutCreateWindow("Hello World");

    init();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
} 


