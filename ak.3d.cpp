// author:	Anton Kratz
// created:	Fri Feb 23 23:23:32 PST 2018
// read in a file line-by-line, and split it by TAB

// compile:	g++ ak.scatter.cpp -o gl -lGL -lGLU -lglut

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
 
/* Initialize OpenGL Graphics */
void initGL() {
	// Set "clearing" or background color
	glClearColor(0,0,0,0);

	GLfloat lightpos[] = {1,1,1,0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0f, 1.0f, 0.0f);	

	glLoadIdentity(); // clear the matrix

	// where it is placed, where it is aimed, and where is up:
	gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

	// glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	// glutSolidTeapot(1.0);
	glutSolidTeapot(1.0);
	glFlush();
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   gluPerspective(0.0, 0.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);          			// Initialize GLUT
	glutInitWindowSize(320, 320);   			// Set the window's initial width & height
	glutInitWindowPosition(50, 50); 			// Position the window's initial top-left corner
	glutCreateWindow("that old teapot");  	// Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}

