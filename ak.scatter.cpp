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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque

	glPointSize(5.0f);
	glEnable(GL_POINT_SMOOTH);

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);

	glEnable(GL_MULTISAMPLE);

	// enable alpha
//	glBlendFunc();	
	glEnable(GL_BLEND);
}
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
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

	glBegin(GL_POINTS);
	glColor4f(0.0f, 0.5f, 0.0f, 0.1f); // Green
	std::cout << "reading file..." << std::endl;
	if (myfile.is_open()) {
		while ( getline (myfile,line) ) {
			boost::split(strs, line, boost::is_any_of("\t"));
			value_x = boost::lexical_cast<double>(strs.at(1));
			value_y = boost::lexical_cast<double>(strs.at(2));

			// std::cout << value_x << "\t" << log10(value_x) << "\t" << log10(value_x)/log10(xmax) << std::endl;	

			glVertex2f(log10(value_x)/log10(xmax), value_y/ymax);

		}
		myfile.close();
	std::cout << "done." << std::endl;
	}

	else std::cout << "Unable to open file"; 

	glEnd();

	glFlush();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);          			// Initialize GLUT
	glutInitWindowSize(320, 320);   			// Set the window's initial width & height
	glutInitWindowPosition(50, 50); 			// Position the window's initial top-left corner
	glutCreateWindow("DESeq2 scatter plot with OpenGL");  	// Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	initGL();                       // Our own OpenGL initialization
	glutMainLoop();                 // Enter the event-processing loop
	return 0;
}

