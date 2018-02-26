// author:	Anton Kratz
// created:	Fri Feb 23 23:23:32 PST 2018
// read in a file line-by-line, and split it by TAB

// compile:	g++ ak.scatter.cpp -o gl -lGL -lGLU -lglut

#include <iostream>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
 
/* Initialize OpenGL Graphics */
void initGL() {
	// Set "clearing" or background color
	glEnable(GL_BLEND);
	   // glShadeModel (GL_FLAT);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

}
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glLoadIdentity ();
	glClear(GL_COLOR_BUFFER_BIT);

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
gluLookAt (-3.0, 0.0, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	
      // glutSolidSphere (1.0, 10.0, 16);	
	// using boost::lexical_cast;	
	
	double value_x, value_y;
	double xmax = 1300;
	double ymax = 7;
		
	std::vector<std::string> strs;

	std::string line;
	std::ifstream myfile ("DESeq2.bound_vs_unbound.txt");
	// std::ifstream myfile ("dummy.txt");

	glLineStipple(1, 0x3F07);
	glEnable(GL_LINE_STIPPLE);


	
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); // red
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	std::cout << "reading file..." << std::endl;
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
			boost::split(strs, line, boost::is_any_of("\t"));
			value_x = boost::lexical_cast<double>(strs.at(1));
			value_y = boost::lexical_cast<double>(strs.at(2));

			// std::cout << value_x << "\t" << log10(value_x) << "\t" << log10(value_x)/log10(xmax) << std::endl;	

			glVertex3f((log10(value_x)/log10(xmax)), (value_y/ymax), 0.0f);
			glVertex3f((log10(value_x)/log10(xmax))-0.01, (value_y/ymax), 0.0f);
			glVertex3f((log10(value_x)/log10(xmax)), (value_y/ymax)-0.01, 0.0f);

			glVertex3f((log10(value_x)/log10(xmax))-0.01, (value_y/ymax), 0.0f);
			glVertex3f((log10(value_x)/log10(xmax))-0.01, (value_y/ymax)-0.01, 0.0f);
			glVertex3f((log10(value_x)/log10(xmax)), (value_y/ymax)-0.01, 0.0f);
		}
		myfile.close();
	std::cout << "done." << std::endl;
	}

	else std::cout << "Unable to open file"; 

	glEnd();
   glutWireCube (1.0);
	glFlush();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   // glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   gluPerspective(60.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	
	glutInit(&argc, argv);          			// Initialize GLUT
	glutInitWindowSize(320, 320);   			// Set the window's initial width & height
	glutInitWindowPosition(50, 50); 			// Position the window's initial top-left corner
	glutCreateWindow("DESeq2 scatter plot with OpenGL");  	// Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	   glutReshapeFunc(reshape);
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}

