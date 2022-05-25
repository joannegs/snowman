//	May Ang
//	mang@ucsc.edu
//	CS 161 - Animation & Visualization
//	Final Project - Rain/Hail/Snow Simulation


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>


#define MAX_PARTICLES 1000
#define WCX		640
#define WCY		480
#define RAIN	0
#define SNOW	1
#define	HAIL	2


float slowdown = 2.0;
float velocity = 0.0;
float zoom = 50.0;
float pan = 0.0;
float tilt = 0.0;
float hailsize = 0.1;

int loop;
int fall;

//floor colors
float r = 0.0;
float g = 1.0;
float b = 0.0;
float ground_points[21][21][3];
float ground_colors[21][21][4];
float accum = -10.0;

typedef struct {
	// Life
	bool alive;	// is the particle alive?
	float life;	// particle lifespan
	float fade; // decay
	// color
	float red; 
	float green;
	float blue;
	// Position/direction
	float xpos; 
	float ypos; 
	float zpos;
	// Velocity/Direction, only goes down in y dir
	float vel;
	// Gravity
	float gravity;
}particles;

// Paticle System
particles par_sys[MAX_PARTICLES]; 	

// Initialize/Reset Particles - give them their attributes
void initParticles(int i) {
		par_sys[i].alive = true;
		par_sys[i].life = 1.0;
		par_sys[i].fade = float(rand()%100)/1000.0f+0.003f;
		
		par_sys[i].xpos = (float) (rand() % 21) - 10;
		par_sys[i].ypos = 10.0;
		par_sys[i].zpos = (float) (rand() % 21) - 10;
		
		par_sys[i].red = 0.5;
		par_sys[i].green = 0.5;
		par_sys[i].blue = 1.0;
		
		par_sys[i].vel = velocity;
		par_sys[i].gravity = -0.8;//-0.8;

}

void init_rain() {
	int x, z;

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    // glClearDepth(20.0);
    glEnable(GL_DEPTH_TEST);

	// Ground Verticies
    // Ground Colors
    for (z = 0; z < 21; z++) {
    	for (x = 0; x < 21; x++) {
    		ground_points[x][z][0] = x - 10.0;
    		ground_points[x][z][1] = accum;
    		ground_points[x][z][2] = z - 10.0;
    	
    		ground_colors[z][x][0] = r; // red value
    		ground_colors[z][x][1] = g; // green value
    		ground_colors[z][x][2] = b; // blue value
    		ground_colors[z][x][3] = 0.0; // acummulation factor
    	}
    }  
    
    // Initialize particles
    for (loop = 0; loop < MAX_PARTICLES; loop++) {
        initParticles(loop);
    }
}

// For Snow
void drawSnow() {
	float x, y, z;
	for (loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
		if (par_sys[loop].alive == true) {			
			x = par_sys[loop].xpos;
			y = par_sys[loop].ypos;
			z = par_sys[loop].zpos + zoom;
			
			// Draw particles
			glColor3f(1.0, 1.0, 1.0);
			glPushMatrix();
			glTranslatef(x, 100, z);
			glutSolidSphere(0.1, 16, 16);
			glPopMatrix();
			
			// Update values
			//Move
			par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
			par_sys[loop].vel += par_sys[loop].gravity;
			// Decay
			par_sys[loop].life -= par_sys[loop].fade;

			if (par_sys[loop].ypos <= -10) {
				int zi = z - zoom + 10;
				int xi = x + 10;
				ground_colors[zi][xi][0] = 1.0;
				ground_colors[zi][xi][2] = 1.0;
				ground_colors[zi][xi][3] += 1.0;
				if (ground_colors[zi][xi][3] > 1.0) {
					ground_points[xi][zi][1] += 0.1;
				}
				par_sys[loop].life = -1.0;
			}

			//Revive 
			if (par_sys[loop].life < 0.0) {
				initParticles(loop);
			}
		}
	}
}


						 
void reshape_snow(int w, int h) {
    if (h == 0) h = 1;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, (float) w / (float) h, .1, 200); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void idle ( ) {
	glutPostRedisplay();
}

/* int main_main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WCX, WCY);
	glutCreateWindow("CMPS 161 - Final Project");
	init_rain();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape_snow);
	glutKeyboardFunc(normal_keys);
	glutSpecialFunc(special_keys);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
} */