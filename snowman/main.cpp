#include <GL/glut.h>

int X, Y;
GLfloat ambient_light[4]={0.2,0.2,0.2,1.0};
GLfloat diffuse_light[4]={0.7,0.7,0.7,1.0};		// color
GLfloat specular_light[4]={1.0, 1.0, 1.0, 1.0};	// brightness
GLfloat light_position[4]={0.0, 50.0, 50.0, 1.0};

void init(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0, 0, 0, 0);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

  // define light parameters
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light); 
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light );
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light );
  glLightfv(GL_LIGHT0, GL_POSITION, light_position );

  // enable changing material color
  glEnable(GL_COLOR_MATERIAL);
  // enable lighting
  glEnable(GL_LIGHTING);  
  glEnable(GL_LIGHT0);

  glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h){
  float aspect = (float)w / (float)h;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, aspect, 0.1, 500.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // specify projection perspective
  gluPerspective(45.0,aspect,0.4,500);

  // init model coordinate system
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
void drawSnowman(){
      // HEAD
    glPushMatrix();
      glColor3f(1.0f, 1.0f, 1.0f);
      glTranslatef(0, -15, 0);
      //glScalef(1.0f,1.0f,1.0f);
      gluSphere(gluNewQuadric(), 15, 25, 25);

      //EYES
      glColor3f(0.5f, 0.5f, 0.5f);
      glPushMatrix();
        glTranslatef(8, 4, 12);
        glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 3, 25, 25);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-8, 4, 12);
        glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 3, 25, 25);
      glPopMatrix();   
      //NOSE
      glColor3f(1.0f, 0.5f, 0.0f);
      glPushMatrix();
        glTranslatef(0, 0, 13);
        glRotatef(0, 1.0, 0.0, 0.0);
        glutSolidCone(3, 15, 100, 25);
      glPopMatrix();

      //SCARF
      /*glColor3f(1.0f, 0.0f, 0.0f);
      glPushMatrix();
        glRotatef(110, 10.0, 0.0, 30.0);
        glutSolidTorus(10, 10, 20, 50);
      glPopMatrix();*/

    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    // BODY
    glPushMatrix();
      glTranslatef(0, -48, 0);
      gluSphere(gluNewQuadric(), 25, 25, 25);

      //BUTTON
      glColor3f(0.0f, 0.0f, 0.0f);
      glPushMatrix();
        glPushMatrix();
        glTranslatef(0, 10, 23);
        glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 2, 25, 25);
      glPopMatrix();

      glPushMatrix();
        glPushMatrix();
        glTranslatef(0, 0, 25);
        glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 2, 25, 25);
      glPopMatrix();

      glPushMatrix();
        glPushMatrix();
        glTranslatef(0, -10, 23);
        glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 2, 25, 25);
      glPopMatrix();
      // ARMS
      glColor3f(0.2f, 0.0f, 0.0f);
      glPushMatrix();
        glTranslatef(20, 0, 0);
        glRotatef(75, -3.0, 10.0, 0.0);
        gluCylinder(gluNewQuadric(), 2, 2, 30, 20, 20);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-50, 10, 0);
        glRotatef(90, 3.0, 10.0, 0.0);
        gluCylinder(gluNewQuadric(), 2, 2, 30, 20, 20);
      glPopMatrix();
      // LEGS
      glColor3f(1.0f, 1.0f, 1.0f);
      glTranslatef(0, -45, 0);
      gluSphere(gluNewQuadric(), 30, 25, 25);

    glPopMatrix();    

}
void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0,-80,350, 0,0,0,0,1,0);

    float cubeSize = 50;

    glRotatef(X, 1,0,0);
    glRotatef(Y, 0,1,0);

    //SglPushMatrix();

    drawSnowman();


    glutSwapBuffers();
}

void specialKeys(int key, int x, int y){
    if (key == GLUT_KEY_RIGHT)
        Y += 5;
  //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT){
        Y -= 5;
    }
    else if (key == GLUT_KEY_UP)
        X += 5;
    else if (key == GLUT_KEY_DOWN)
        X -= 5;
    //  Request display update
    glutPostRedisplay();
}
int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(200, 100);
  glutInitWindowSize(1080, 720);
  glutCreateWindow("Hello World");

  init();

  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutSpecialFunc(specialKeys);
  glutMainLoop();
}
