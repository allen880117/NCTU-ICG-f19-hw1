//Your Student ID is 0616309. (Modify it)
#include "glut.h"
#include <iostream>
#include "math.h"
using namespace std;

#define PI acos(-1)

void display();
void reshape(int _width, int _height);
void keyboard(unsigned char key, int x, int y);
void idle();

void drawSphere(double, int ,int, float, float, float);
void drawSun();
void drawEarth(double, int, int);
void drawMoon();
void drawAxis();

/*
	glRotatef() & glTranslatef()

	are Moving "Local Coordinate".

*/

int width = 400, height = 400;
int X = 1; //default degree value, you can adjust it
GLfloat Y = 0.5; //default radius value, you can adjust it

GLfloat Earth_Rotation = (GLfloat)X;
GLfloat Earth_Revolution = (GLfloat)X / (GLfloat)365.0f;
GLfloat Earth_Revolution_Radius = (GLfloat)18.0f;
GLfloat Earth_Radius = (GLfloat)2.0f * Y;
GLfloat Earth_Obliquity = (GLfloat)23.5f;

int Earth_Slices = 360;
int Earth_Stacks = 180;

GLfloat Earth_Axis_Length = (GLfloat)8.0f * Y;
GLfloat Earth_Axis_Radius = (GLfloat)0.5f * Y;

GLfloat Moon_Rotation = (GLfloat)X / (GLfloat) 28.0f;
GLfloat Moon_Revolution = (GLfloat)X / (GLfloat) 28.0f;
GLfloat Moon_Revolution_Radius = (GLfloat) 3.0f;

int time_flow = 1;
int pass_time_mode = 1;
float pass_time_1 = 0.025f;
float pass_time_2 = 1.0f;
float pass_time = pass_time_1;
float time_counter = 0.0f;
float moon_time_counter = 0.0f;
float earth_time_counter = 0.0f;

void drawBox();

GLfloat u = 90.0f;
GLfloat theta_u = 0.025f;
GLfloat r = 1.0f;

void lighting()
{
	// enable lighting
	glEnable(GL_LIGHTING);
	//Add directed light
	GLfloat diffuseColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat ambientColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };	
	GLfloat position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glEnable(GL_LIGHT0);								//open light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);	    //set diffuse color of light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);	    //set ambient color of light0
	glLightfv(GL_LIGHT0, GL_POSITION, position);		//set position of light0

	// For Color and Shade // WACODE
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL); 
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("HW1");

	lighting();
	glutDisplayFunc(display);
	
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

void display()
{   	
	// TO DO: Set the MVP transform
	//ModelView Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//Viewport Matrix
	glViewport(0, 0, width, height);
	//Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, width / (GLfloat)height, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);		//remove back face
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);		//normalized normal 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// TO DO: Draw the Sun, Earth, Moon
	/*
	// Sun
		glPushMatrix();
		drawSun();
		glPopMatrix();

	// Earth & Moon (Remeber M*R*T*(obj) )

		glPushMatrix();
		
		// Revolution(around Sun) (R T)
		GLfloat RevolutionAngle = 360.0f*Earth_Revolution*time_counter;
		glRotatef(RevolutionAngle, 0.0f, 1.0f, 0.0f); // Rotate "Local Coord" around "Local Y-axis"
		glTranslatef(0.0, 0.0f, Earth_Revolution_Radius); // Translate "Local Coord" along "Local Z-axis"
		
		glRotatef(-RevolutionAngle, 0.0f, 1.0f, 0.0f); // Rotate Back
		
		// Earth
			glPushMatrix();

			// Obliquity (R)
			glRotatef(-Earth_Obliquity, 0.0f, 0.0f, 1.0f); // Rotate "Local Coord" around "Local X-axis"

			// Draw (with self-Rotation)
			drawAxis();
			drawEarth(Earth_Radius, Earth_Slices, Earth_Stacks);
	
			glPopMatrix();

		// Moon
			glPushMatrix();
			
			// Revolution(around Earth)
			glRotatef(360.0f*Moon_Revolution*moon_time_counter, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, Moon_Revolution_Radius);

			// Draw (with self-Rotation)
			drawMoon();
			
			glPopMatrix();

		glPopMatrix();
	*/
	drawSphere(1, 4, 2, 1.0, 1.0, 1.0);
	drawBox();

	glPushMatrix();
		
		GLfloat tz = -r * cos(u * PI / 180);
		GLfloat ty = r * sin(u * PI / 180);
		
		glTranslatef(0.0, ty, tz); // Translation * Pn
		glRotatef(90, 1.0, 0.0, 0.0); // R_X * Translation * Pn
		glScalef(2, 1, 1); // S * R_X * Translation * Pn
		glTranslatef(0.0, 0.0, -0.5); // Tz * S * R_X * Translation * Pn

		drawBox();
	
	glPopMatrix();
	// Swap Buffer(Important) to draw
	glutSwapBuffers();
}

void reshape(int _width, int _height) {
	width = _width;
	height = _height;
}

void keyboard(unsigned char key, int x, int y) {
	// TO DO: Set the keyboard control
	switch (key)
	{
	case 'o': case 'O': 
		Earth_Slices = (Earth_Slices == 360) ? 4 : 360;
		Earth_Stacks = (Earth_Stacks == 180) ? 2 : 180;
		break;
	case 'p': case 'P': 
		time_flow = (time_flow == 1) ? 0 : 1; 
		break;
	
	case 'i': case 'I':
		pass_time_mode = (pass_time_mode == 1) ? 2 : 1;
		switch (pass_time_mode) {
		case 1: pass_time = pass_time_1; break;
		case 2: pass_time = pass_time_2; break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void idle() {
	glutPostRedisplay();
	if (time_flow == 1) {
		time_counter = (time_counter + pass_time >= 365.0f) ? 0.0f : time_counter + pass_time;
		moon_time_counter = (moon_time_counter + pass_time >= 28.0f) ? 0.0f : moon_time_counter + pass_time;
		earth_time_counter = (earth_time_counter + pass_time >= 1.0f) ? 0.0f : earth_time_counter + pass_time;
	}

	if (time_flow == 0) {
		u += theta_u;
		if (u >= 360.0f) u = 0.0f;
	}
}

void drawSphere(double radius, int slices, int stacks, float R, float G, float B) {

	/*
		How to draw Sphere:
			Image there is a octagon on X-Z plane.

			Now rotate it along Z-axis with small angle;
		We can choose two adjacent point in original octagon,
		and two adjacent point which are actually the two points we chose before and be rotated.
		the four points can form an "QUAD",

			Rotate octagon along Z-axis many time, and each time do same thing
		we mentioned above.
			
			A set of two points with many rotating, we will got a "QUAD_STRIP"
			Many set of two points with many rotating, we will got many "QUAD_STRIPs";

			Combine (or glue up) these "QUAD_STRIPS",
		which basically we can say it's a rough "Sphere".
		
		Ref:
			https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere
	*/

	/*
		Slices and Stacks
		Ref Image:
		https://www.researchgate.net/figure/a-The-construction-of-a-sphere-with-8-stacks-16-slices-and-144-vertices-Vertices_fig13_266873735
	*/

	int horizon = slices;
	int vertical = stacks * 2;

	double horizonTheta = double(PI*double(2.0) / double(horizon));
	double verticalTheta = double(PI*double(2.0) / double(vertical));

	// Draw a "Sphere"
	// Or we can say drawing many adjacent "QUAD_STRIP"s
	for (int i = 0; i < horizon; i++) { 
		// Draw a "QUAD_STRIP"
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= vertical; j++) {
			// Since we have to "Close" the quad_strip
			// we have to overlap the start edge
			
			// p1 xyz norm
			double p1x = cos(j * verticalTheta) * cos(i * horizonTheta);
			double p1y = sin(j * verticalTheta);
			double p1z = cos(j * verticalTheta) * sin(i * horizonTheta);
			// p2 xyz norm
			double p2x = cos(j * verticalTheta) * cos(double(i+1) * horizonTheta);
			double p2y = sin(j * verticalTheta);
			double p2z = cos(j * verticalTheta) * sin(double(i+1) * horizonTheta);

			// draw p1
			glColor3f(R, G, B);
			glNormal3f(p1x, p1y, p1z); //Specify Vertex's normal vector. Without this, No Shadering
			glVertex3f(radius*p1x, radius*p1y, radius*p1z);
			
			// draw p2
			glColor3f(R, G, B);
			glNormal3f(p2x, p2y, p2z); //Specify Vertex's normal vector. Without this, No Shadering
			glVertex3f(radius*p2x, radius*p2y, radius*p2z);
		}
		glEnd();
	}
}

void drawSun() {
	drawSphere(7*Y, 240, 60, 1.0f, 0.0f, 0.0f);
}

void drawEarth(double radius, int slices, int stacks) {
	glPushMatrix();
	float angle = 360.0f * Earth_Rotation * earth_time_counter;
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	drawSphere(radius, slices, stacks, 0.0f, 0.0f, 1.0f);
	glPopMatrix();
}

void drawMoon() {
	glPushMatrix();
	float angle = 360.0f * Moon_Rotation * moon_time_counter;
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	drawSphere(Y, 240, 60, 1.0f, 1.0f, 1.0f);
	glPopMatrix();
}

void drawAxis() {
	glPushMatrix();

	// Since the Cylinder is along Z-axis and Bottom at origin, Top at Z = length
	// We have to Rotate itself as being along Y-axis
	// Along vector(1.0f, 0.0f, 0.0f)(which also means X-axis) rotate 90 degrees(clock-wise)
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotate "Local Coord" around "Local X-axis"
	// Move Cylinder, that its middle will be at origin
	glTranslatef(0.0f, 0.0f, -Earth_Axis_Length / 2.0f); // Translate "Local Coord" along "Local Y-axis"

	// Draw
	glColor3f(0.0f, 1.0f, 0.0f);
	GLUquadricObj *qobj = gluNewQuadric();
	gluCylinder(qobj, Earth_Axis_Radius, Earth_Axis_Radius, Earth_Axis_Length, 32, 5);
	
	glPopMatrix();
}

void drawBox() {
	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glNormal3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		
		glNormal3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);
		
		glNormal3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		
		glNormal3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);

	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glNormal3f(0.5, 0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);

		glNormal3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);

		glNormal3f(-0.5, -0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.5);

		glNormal3f(-0.5, 0.5, 0.5);
		glVertex3f(-0.5, 0.5, 0.5);

	glEnd();
}