#include <GL/glut.h>
#include <math.h>

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
  gluPerspective(45.0, aspect, 0.1, 1000.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // specify projection perspective
  gluPerspective(45.0,aspect,0.4,1000);

  // init model coordinate system
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void drawGround(){
  glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0,0,23);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
      //glNormal3f(1.0, 0.0, 0.0);
      glVertex3f(1000, 1000, 100);
      glVertex3f(-1000, 1000, 100);
      glVertex3f(-1000, -1000, 100);
      glVertex3f(1000, -1000, 100);
    glEnd();
  glPopMatrix();
 // glRotatef(-90,1,0,0);
}

void drawTree(int x, int z){
  // tronco da árvore
    glPushMatrix();
      glTranslatef(x, -120, -z);
      glColor3f(1.0f, 0.4f, 0.0f);
      glRotatef(270, 1, 0, 0);
      gluCylinder(gluNewQuadric(), 5, 0, 120, 20, 20);
    glPopMatrix(); 

    // cone 1 da arvore 
    glColor3f(0.0f, 1.0f, 0.3f);
    glPushMatrix();
      glTranslatef(x, -40, -z);
      glRotatef(270, 1, 0, 0);
      gluCylinder(gluNewQuadric(), 25, 0, 40, 20, 20);
    glPopMatrix(); 

    // cone 2 da arvore 
    glColor3f(0.0f, 1.0f, 0.5f);
    glPushMatrix();
      glTranslatef(x, -65, -z);
      glRotatef(270, 1, 0, 0);
      gluCylinder(gluNewQuadric(), 40, 0, 40, 20, 20);
    glPopMatrix(); 

    // cone 3 da arvore 
    glColor3f(0.0f, 1.0f, 0.7f);
    glPushMatrix();
      glTranslatef(x, -90, -z);
      glRotatef(270, 1, 0, 0);
      gluCylinder(gluNewQuadric(), 55, 0, 40, 20, 20);
    glPopMatrix(); 
}

void drawSnowman(){
    // HEAD
    // has eyes and nose inside the head 
    glPushMatrix();
      glColor3f(1.0f, 1.0f, 1.0f);
      glTranslatef(0, -15, 0);
      //glScalef(1.0f,1.0f,1.0f);
      gluSphere(gluNewQuadric(), 15, 25, 25);

      //EYES
      glColor3f(0.5f, 0.5f, 0.5f); // set eye color
      glPushMatrix(); //right eye
        glTranslatef(8, 4, 12); // floatX, floatY, floatZ
        //glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 3, 25, 25); //Specifies the quadrics object, radius, subdivisions around the z axis, subdivisions along the z axis
      glPopMatrix();

      glPushMatrix(); //left eye
        glTranslatef(-8, 4, 12);
        //glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 3, 25, 25);
      glPopMatrix();  
       
      //NOSE
      glColor3f(1.0f, 0.5f, 0.0f);
      glPushMatrix();
        glTranslatef(0, 0, 13);
        //glRotatef(0, 1.0, 0.0, 0.0);
        glutSolidCone(3, 15, 100, 25); // radius of the base, height, ubdivisions around the Z axis, subdivisions along the Z axis
      glPopMatrix();
    
    glPopMatrix();

    //SCARF
    // a red scarf
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
      glTranslatef(0, -28, 0);
       glRotatef(90, 1.0, 0.0, 0.0);
       glutSolidTorus(6, 10, 20, 50);
    glPopMatrix();
    

    // HAT
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix(); // base of hat
      //glTranslatef(0, 0, 0);
      glRotatef(90, 1.0, 0.0, 0.0);
      glutSolidTorus(5, 13, 20, 20); 
    glPopMatrix();

    glPushMatrix(); // hat body
        glTranslatef(0, 3, 0);
        glRotatef(180, 0.0, 10.0, 10.0); // angle, floatX, floatY, floatZ
        gluCylinder(gluNewQuadric(), 10, 10, 20, 20, 20); // quadrics object, base radius, top radius, heigth, slices, stacks
      glPopMatrix();

  // tampa do chapel 
  glPushMatrix(); 
        glTranslatef(0, 23, 0);
        glRotatef(180, 0.0, 10.0, 10.0); 
        gluDisk(gluNewQuadric(), 0, 10, 90, 1); 
    glPopMatrix(); 

    // BODY
    // has the buttons and arms inside
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
      glTranslatef(0, -48, 0);
      gluSphere(gluNewQuadric(), 25, 25, 25);

      //BUTTON
      // three black buttons
      glColor3f(0.0f, 0.0f, 0.0f);
      glPushMatrix();
        glPushMatrix();
        glTranslatef(0, 10, 23);
        //glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 2, 25, 25);
      glPopMatrix();

      glPushMatrix();
        glPushMatrix();
        glTranslatef(0, 0, 25);
        //glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 2, 25, 25);
      glPopMatrix();

      glPushMatrix();
        glPushMatrix();
        glTranslatef(0, -10, 23);
        //glRotatef(0, 1.0, 0.0, 0.0);
        gluSphere(gluNewQuadric(), 2, 25, 25);
      glPopMatrix();

      // ARMS
      glColor3f(0.2f, 0.0f, 0.0f);
      glPushMatrix();
        glTranslatef(20, 0, 0);
        glRotatef(75, -3.0, 10.0, 0.0); // angle, floatX, floatY, floatZ
        gluCylinder(gluNewQuadric(), 2, 2, 30, 20, 20); // quadrics object, base radius, top radius, heigth, slices, stacks
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

    glRotatef(X, 1,0,0);
    glRotatef(Y, 0,1,0);

    //SglPushMatrix();

    drawGround();
    drawTree(150, 150);
    drawTree(-150, 100);
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