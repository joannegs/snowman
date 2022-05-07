#include <GL/glut.h>

using namespace std;

GLint rotateX, rotateY;
GLfloat angle, aspect, cubeSize, gap;
float z1,z2,z3;
void init(){
  cubeSize = 30;
  rotateX = 0;
  rotateY = 0;
  z1 = 0;
  z2 = 0;
  z3 = 0;
  angle = 45;
  gap = 1;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
  aspect = (float)w / (float)h;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, aspect, 0.1, 500.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // specify projection perspective
  gluPerspective(angle,aspect,0.4,500);

  // init model coordinate system
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void rotateZ(int i){
		if(i == 0){
			glRotatef(z1,0,0,1);
    }
		else if(i == 1) {
			glRotatef(z2,0,0,1);
    }
		else if(i == 2) {
			 glRotatef(z3,0,0,1);
		}
		
		
	}

void drawCube(int x, int y, int z){
  glPushMatrix();

  // translate to final position
  glTranslatef((x - 1) * cubeSize + x * gap, (y - 1) * cubeSize + y * gap, (z - 1) * cubeSize + z * gap);

  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);  // front
    glNormal3f(0.0, 0.0, 1.0);  // face normal
    glVertex3f(cubeSize/2, cubeSize/2, cubeSize/2);
    glVertex3f(-cubeSize/2, cubeSize/2, cubeSize/2);
    glVertex3f(-cubeSize/2, -cubeSize/2, cubeSize/2);
    glVertex3f(cubeSize/2, -cubeSize/2, cubeSize/2);
  glEnd();

  glColor3f(1.0f, 0.5f, 0.0f);
  glBegin(GL_QUADS);  // back
    glNormal3f(0.0, 0.0, -1.0);  // face normal
    glVertex3f(cubeSize/2, cubeSize/2, -cubeSize/2);
    glVertex3f(cubeSize/2, -cubeSize/2, -cubeSize/2);
    glVertex3f(-cubeSize/2, -cubeSize/2, -cubeSize/2);
    glVertex3f(-cubeSize/2, cubeSize/2, -cubeSize/2);
  glEnd();

  glColor3f(0.0f, 0.0f, 1.0f);
  glBegin(GL_QUADS);  // left
    glNormal3f(-1.0, 0.0, 0.0);  // face normal
    glVertex3f(-cubeSize/2, cubeSize/2, cubeSize/2);
    glVertex3f(-cubeSize/2, cubeSize/2, -cubeSize/2);
    glVertex3f(-cubeSize/2, -cubeSize/2, -cubeSize/2);
    glVertex3f(-cubeSize/2, -cubeSize/2, cubeSize/2);
  glEnd();
  
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // right
    glNormal3f(1.0, 0.0, 0.0);  // face normal
    glVertex3f(cubeSize/2, cubeSize/2, cubeSize/2);
    glVertex3f(cubeSize/2, -cubeSize/2, cubeSize/2);
    glVertex3f(cubeSize/2, -cubeSize/2, -cubeSize/2);
    glVertex3f(cubeSize/2, cubeSize/2, -cubeSize/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);  // top
    glNormal3f(0.0, 1.0, 0.0);  // face normal
    glVertex3f(-cubeSize/2, cubeSize/2, -cubeSize/2);
    glVertex3f(-cubeSize/2, cubeSize/2, cubeSize/2);
    glVertex3f(cubeSize/2, cubeSize/2, cubeSize/2);
    glVertex3f(cubeSize/2, cubeSize/2, -cubeSize/2);
  glEnd();

  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);  // bottom
    glNormal3f(0.0, -1.0, 0.0);  // face normal
    glVertex3f(-cubeSize/2, -cubeSize/2, -cubeSize/2);
    glVertex3f(cubeSize/2, -cubeSize/2, -cubeSize/2);
    glVertex3f(cubeSize/2, -cubeSize/2, cubeSize/2);
    glVertex3f(-cubeSize/2, -cubeSize/2, cubeSize/2);
  glEnd();

  glPopMatrix();
}

void draw(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // reset transformations
  glLoadIdentity();


  // camera;
  gluLookAt(0,80,200, 0,0,0, 0,1,0);

  // apply visualization transformations
  glRotatef(rotateX, 1.0, 0.0, 0.0); 
  glRotatef(rotateY, 0.0, 1.0, 0.0); 

  for (int i = 0; i < 3; ++i){ // x
    
    for (int j = 0; j < 3; ++j){// y
      for (int k = 0; k < 3; ++k){ //z
        
        
        drawCube(i, j, k);
      }
    }
  }


  glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{

  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotateY += 5;
  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT){
    rotateY -= 5;
  }
  else if (key == GLUT_KEY_UP)
    rotateX += 5;
  else if (key == GLUT_KEY_DOWN)
    rotateX -= 5;
  //  Request display update
  glutPostRedisplay();
}

void keyboard_func(unsigned char key, int x, int y)
{

  switch(key) {

    case 'q':
    case 'Q':
      z1 += 5;
    break;

    default:
      break;

  }
  glutPostRedisplay();
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(200, 100);
  glutInitWindowSize(1080, 720);
  glutCreateWindow("Hello World");

  init();
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(keyboard_func);

  glutMainLoop();
}
