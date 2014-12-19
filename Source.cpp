/*******************************************************************
Example of Matrix Stacks
********************************************************************/

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void init(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void arrowKeys(int key, int x, int y);

void spinDisplay(int);



#define PI 3.141592654



// Set up lighting/shading and material properties - upcoming lecture
GLfloat mat_ambient[] = { 0.4, 0.2, 0.0, 1.0 };
GLfloat mat_specular[] = { 0.4, 0.4, 0.0, 1.0 };
GLfloat mat_diffuse[] = { 0.9, 0.5, 0.0, 1.0 };
GLfloat mat_shininess[] = { 0.0 };
GLfloat light_position0[] = { -5.0, 0.0, 5.0, 1.0 };
GLfloat light_position1[] = { 5.0, 0.0, 5.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat model_ambient[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat mat1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat1_specular[] = { 0.45, 0.55, 0.45, 1.0 };
GLfloat mat1_diffuse[] = { 0.1, 0.35, 0.1, 1.0 };
GLfloat mat1_shininess[] = { 0.25 };

GLuint startList;
GLUquadricObj *qobj;
static GLfloat spin = 0.0;
static GLfloat theta = 0.0;
float sf = 1.0;
int currentKey = 0;


/* Initialize the system */
void init(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Setup lighting and material props.
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);

}




void display(void)
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Set up the Viewing Transformation (V matrix)
	gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Set up Modeling Transformation (M matrix)
	//glRotatef(spin,1.0,1.0,1.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	for (int j = 0; j<12; j++)
	{
		glPushMatrix();

		glRotatef(30.0*j, 0.0, 0.0, 1.0);
		glTranslatef(5.0, 0.0, 0.0);
		glScalef(1.0, 0.5, 0.5);
		glutSolidCube(1.0);
		glPopMatrix();
	}

	glutSolidSphere(0.5, 20, 20);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat1_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat1_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat1_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shininess);

	// minute hand
	glPushMatrix();
	glRotatef(30.0, 0.0, 0.0, 1.0);
	glTranslatef(2.0, 0.0, 0.0);
	glScalef(6.0, 0.25, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	// hour hand
	glPushMatrix();
	glRotatef(145.0, 0.0, 0.0, 1.0);
	glTranslatef(1.25, 0.0, 0.0);
	glScalef(4.5, 0.25, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	// second hand
	glPushMatrix();
	glRotatef(-theta, 0.0, 0.0, 1.0);
	glTranslatef(2.0, 0.0, 0.0);
	glScalef(6.0, 0.1, 0.25);
	glutSolidCube(1.0);
	glPopMatrix();
	glutSwapBuffers();
}



/* called at initialization and whenever user resizes the window */
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 0.1, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

/* Called when an arrow key has been detected */

void arrowKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		sf -= 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_UP:
		sf += 0.5;
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		glutPostRedisplay();
		break;
	default:
		break;
	}

}

/* Handles input from the keyboard, non-arrow keys */
void keyboard(unsigned char key, int x, int y)
{
	currentKey = key;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutTimerFunc(1000, spinDisplay, 0);

		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}


void spinDisplay(int)
{
	spin += 1.0;
	if (spin > 360.0)
		spin -= 360.0;

	theta += 6.0;
	if (theta > 360.0)
		theta -= 360.0;

	glutPostRedisplay();
	glutTimerFunc(1000, spinDisplay, 0);
}





int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init(500, 500);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrowKeys);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}

