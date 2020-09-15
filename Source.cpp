#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

static int draw_cube = 1; // option to draw the cube
static int cubeRotating = 0; // on/off rotaion of the cube
static int cubeColor = 0; //to change the color of the cube
static int cubeRotateAngle = 0; // current rotation angle of the cube

static int draw_pyramid = 1; // option to draw the pyramid
static int pyramidRotating = 0; // on/off rotaion of the pyramid
static int pyramidColor = 0; //to change the color of the pyramid
static int pyramidRotateAngle = 0; // current rotation angle of the pyramid

// Draw a 3sided pyramid of size 1.3
void pyramid(int p_frame) {

	if (p_frame) {
		// Set pyramid frame mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.0f, 0.0f, 0.0f); 
	}
	else {
		// Set fill-mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (!pyramidColor) 
			glColor3f(1, 0, 0);
		else glColor3f(0, 1, 0);
	}

	// Draw the base with 3 points
	glBegin(GL_QUADS);
	glVertex3f(-1.3, 0, -1.3);
	glVertex3f(-1.3, 0, 1.3);
	glVertex3f( 1.3, 0, 1.3);
	glVertex3f( 1.3, 0,-1.3);
	glEnd();

	// Draw three side triangles
	glBegin(GL_TRIANGLE_FAN);

	// the commond point of the three triangles
	glVertex3f(0, 2, 0);

	// Base points of each triangle
	glVertex3f(-1.3, 0, -1.3);
	glVertex3f(-1.3, 0, 1.3);//SIDE1

	glVertex3f(-1.3, 0, 1.3);
	glVertex3f( 1.3, 0, 1.3);//SIDE2

	glVertex3f(1.3, 0, 1.3);
	glVertex3f(1.3, 0, -1.3);//SIDE3

	glVertex3f(1.3, 0, -1.3);
	glVertex3f(-1.3, 0, -1.3); //SIDE 4
	glEnd();

}

// Draw a cube of size 1.5, with one corner at (0,0,0)
void cube(int c_frame) {

	if (c_frame) {
		// Set wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	else {
		// Set fill-mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (!cubeColor) {
			glColor3f(0, 0, 1);
		}
		else glColor3f(0, 1, 0);
	}

	glBegin(GL_QUADS);

	// bottom side
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1.5);
	glVertex3f(1.5, 0, 1.5);
	glVertex3f(1.5, 0, 0);

	// top side
	glVertex3f(0,   1.5, 0);
	glVertex3f(0,   1.5, 1.5);
	glVertex3f(1.5, 1.5, 1.5);
	glVertex3f(1.5, 1.5, 0);

	// front side
	glVertex3f(0,   0,   0);
	glVertex3f(0,   1.5, 0);
	glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.5, 0,   0);

	// back side
	glVertex3f(0,   0,   1.5);
	glVertex3f(0,   1.5, 1.5);
	glVertex3f(1.5, 1.5, 1.5);
	glVertex3f(1.5, 0,   1.5);

	// left side
	glVertex3f(0, 0,   0);
	glVertex3f(0, 0,   1.5);
	glVertex3f(0, 1.5, 1.5);
	glVertex3f(0, 1.5, 0);

	// right side
	glVertex3f(1.5, 0,   0);
	glVertex3f(1.5, 0,   1.5);
	glVertex3f(1.5, 1.5, 1.5);
	glVertex3f(1.5, 1.5, 0);

	glEnd();
}

// Handle key-pressed even
void byKeyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'c': case 'C': // set options to draw the cube only
		draw_cube = 1;
		draw_pyramid = 0;
		cubeColor = 0;
		break;
	case 'g': case 'G': // set options to change the color
		draw_cube = 1;
		draw_pyramid = 1;
		pyramidColor = 1;
		cubeColor = 1;
		break;
	case 'p': case 'P': // set options to draw the pyramid only
		draw_cube = 0;
		draw_pyramid = 1;
		pyramidColor = 0;
		break;
	case 'b': case 'B': // set options to draw both objects
		draw_cube = 1;
		draw_pyramid = 1;
		pyramidColor = 0;
		cubeColor = 0;
		break;
	case 27: // ESC key
		exit(0);
		break;
	}

	glutPostRedisplay();
}

// function to update rotation of the cube
void timer_for_cube(int cframe)
{
	cubeRotateAngle += 1; // make the cube rotate
	glutPostRedisplay();	// update the display

							// set timer for update for next frame
	if (cubeRotating) {
		glutTimerFunc(20, timer_for_cube, 0);
	}
	
}
void timer_for_p(int pframe)
{
	pyramidRotateAngle += 1; // make the pyramid rotate
	glutPostRedisplay();	// update the display

							// set timer for update for next frame for the pyramid
	if (pyramidRotating) {
		glutTimerFunc(20, timer_for_p, 0);// frame = 0; 20 for speed
	}

}
// Handle mouse-button pressed to turn on/off the animation 
void byMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		cubeRotating = !cubeRotating;

		if (cubeRotating) {
			// Start the timer
			glutTimerFunc(40, timer_for_cube, 0);
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		pyramidRotating = !pyramidRotating;

		if (pyramidRotating) {
			// Start the timer
			glutTimerFunc(40, timer_for_p, 0);
		}
	}
}


// Display the scene
void Display(void) {

	// Reset the drawing buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the cube if requested
	if (draw_cube) {
		glPushMatrix();
		// Place the cube into the scene
		glTranslatef(-2.1, 1.5, 1);
		// Rotate the cube (as its current rotation angle)
		glRotatef(cubeRotateAngle, 1, 1, 1);
		// make the rotation axis going through the center of the cube
		glTranslatef(-0.5f, -0.5f, -0.5f);

		cube(0); // draw the c_frame version
		cube(1); // draw color version

		glPopMatrix();
	}

	// Draw the pyramid if requested
	if (draw_pyramid) {
		glPushMatrix();

		// Pose the pyramid
		glTranslatef(1.5, -1.5, 0);
		// Rotate the pyramid (as its oposite rotation angle)
		glRotatef(pyramidRotateAngle, 0, -1, 0);
		// make the rotation axis going through the center of the pyramid
		glTranslatef(0.0f, 0.0f, 0.0f);
		

		pyramid(0); // draw wireframe version
		pyramid(1); // draw color version

		glPopMatrix();
	}

	glFlush();
	glutSwapBuffers();
}

// Called when the window is resized.
void Reshape(int w, int h) {

	glViewport(0, 0, w, h);

	// Setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 200.0);

	// Setup model view matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 5.0, 7.0, // look from
		      0.0, 0.0, 0.0, // look to
		      0.0, 1.0, 0.0);
}

// Initialize OpenGL parameters 
//Background
void init_bg() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black background
	glEnable(GL_DEPTH_TEST); // Enable depth-test to remove hidden faces
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GRAFIKA KOMPJUTERIKE");

	// Setup callback functions
	init_bg();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(byKeyboard);
	glutMouseFunc(byMouse);
	glutMainLoop();
	return 0;
}