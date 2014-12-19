/*******************************************************************
Interactive 3D City Modelling Program
********************************************************************/
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <utility>
#include <vector>
#include "VECTOR3D.h"
#include "cube.h"
#include "TerrainGrid.h"
#include <cmath>

void initOpenGL(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void deselectAll();
void keyboard(unsigned char key, int x, int y);
void functionKeys(int key, int x, int y);
int currentActiveSizeOfCubeArray();


static int currentButton;
static unsigned char currentKey;

GLfloat light_position0[] = { 12.0, 6.0, -12.0, 1.0 };
GLfloat light_position1[] = { -12.0, 6.0, 12.0, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
FILE *fileToOpen;


// Cubes
// you may want to create a fixed size array of cubes or a fixed size array of pointers to cubes
// and othr variables to keep track of the number of current cubes etc.
// see cube.h createCube function
Cube *arrayOfCubes[100];
int selected = -1;
int mode = -1;
boolean multipleSelect = false;
// Terrain Grid
TerrainGrid *terrainGrid = NULL;

int gridSize = 16;

int main(int argc, char **argv)
{
	//arrayOfCubes[0] = (Cube*)calloc(1, sizeof(Cube));
	//memset(arrayOfCubes, '\0', sizeof(arrayOfCubes));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("City Builder");

	initOpenGL(750, 750);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotionHandler);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(functionKeys);
	glutMainLoop();
	return 0;
}



// Setup openGL */
void initOpenGL(int w, int h)
{
	// Set up viewport, projection, then change to modelview matrix mode - 
	// display function will then set up camera and modeling transforms
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(70.0, 1.0, 0.2, 80.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set up and enable lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_NORMALIZE);

	// Set up Terrain Grid
	VECTOR3D origin = VECTOR3D(-8.0f, 0.0f, 8.0f);		// Terrain bounds: -8.0 to 8.0 in x and z direction
	terrainGrid = new TerrainGrid(gridSize, 16.0);	// size of terrain is therefore 16.0
	terrainGrid->InitGrid(gridSize, origin, 16.0, 16.0);
}



void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// Set up fixed camera position and where it is looking, it's orientation
	gluLookAt(-12.0, 6.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//      Eye X    Y   Z  Center X  Y  Z  UP   X   Y    Z

	// Add code to draw all cubes currently in your array
	// see cube.h drawCube()
	//drawCube(createCube());
	for (int i = 0; i < 100; i++) {
		if (arrayOfCubes[i] != NULL) {
			//glColor3f(1.0, 0.0, 0.0);
			drawCube(arrayOfCubes[i]);
		}
	}

	// Draw Terrain
	terrainGrid->DrawGrid(gridSize);
	glutSwapBuffers();
}


// Called at initialization and whenever user resizes the window */
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 0.2, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

VECTOR3D pos = VECTOR3D(0, 0, 0);

void mouse(int button, int state, int x, int y)
{
	currentButton = button;

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{

		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{

		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void mouseMotionHandler(int xMouse, int yMouse)
{
	if (currentButton == GLUT_LEFT_BUTTON)
	{
	//	myCube = createCube();
	}
	glutPostRedisplay();
}

void deselectAll(){
	multipleSelect = false;
	mode = -1;
	for (int i = 0; i < 100; i++){
		if (arrayOfCubes[i] != NULL)
			((Cube*)arrayOfCubes[i])->selected = false;
	}
	selected = -1;
}
/* Handles input from the keyboard, non-arrow keys */
void keyboard(unsigned char key, int x, int y)
{
	int err;
	int lineCounter;
	float a, b, c, d, e, f, g;
	switch (key)
	{
	case 't': // set to translate mode 1
		mode = 1;
		break;
	case 's': // set to scale mode 2
		mode = 2;
		break;
	case 'r': // set to rotate mode 3
		mode = 3;
		break;
	case 'h': //set to height mode 4
		mode = 4;
		break;
	case 'c': //change selection of cube 5
		mode = 5;
		if (selected == -1){
			selected = 0;
			((Cube*)arrayOfCubes[abs(selected)])->selected = true;
		}
		break;
	case '+':
		//if (mode == 5){
		multipleSelect = true;
			mode = 6;
		//}
		break;
	case '-':
		deselectAll();
		break;
	case 'w':
		deselectAll();

		err = fopen_s(&fileToOpen, "city.txt", "w");
		for (int i = 0; i < 100; i++){
			if (arrayOfCubes[i] != NULL)
				fprintf(fileToOpen, "%f %f %f %f %f %f %f\n", ((Cube*)arrayOfCubes[i])->angle, ((Cube*)arrayOfCubes[i])->tx, ((Cube*)arrayOfCubes[i])->ty, ((Cube*)arrayOfCubes[i])->tz, ((Cube*)arrayOfCubes[i])->sfx, ((Cube*)arrayOfCubes[i])->sfy, ((Cube*)arrayOfCubes[i])->sfz);	
		}
		fclose(fileToOpen);
		break;
	case 'l':
		deselectAll();
		 err = fopen_s(&fileToOpen, "city.txt", "r");
		 lineCounter = 0;
		 if (err == 0){
			 //while (fscanf_s(fileToOpen, "%f %f %f %f %f %f %f\n", &(((Cube*)arrayOfCubes[lineCounter])->angle), &(((Cube*)arrayOfCubes[lineCounter])->tx), &(((Cube*)arrayOfCubes[lineCounter])->ty), &(((Cube*)arrayOfCubes[lineCounter])->tz), &(((Cube*)arrayOfCubes[lineCounter])->sfx), &(((Cube*)arrayOfCubes[lineCounter])->sfy), &(((Cube*)arrayOfCubes[lineCounter])->sfz)) != EOF){
			 //	 lineCounter++;
			 //	}
			 while (fscanf_s(fileToOpen, "%f %f %f %f %f %f %f\n", &a, &b, &c, &d, &e, &f, &g) != EOF){
				 arrayOfCubes[lineCounter] = (Cube*)calloc(1, sizeof(Cube));
				 arrayOfCubes[lineCounter] = createCube();
				 ((Cube*)arrayOfCubes[lineCounter])->angle = a;
				 ((Cube*)arrayOfCubes[lineCounter])->tx = b;
				 ((Cube*)arrayOfCubes[lineCounter])->ty = c;
				 ((Cube*)arrayOfCubes[lineCounter])->tz = d;
				 ((Cube*)arrayOfCubes[lineCounter])->sfx = e;
				 ((Cube*)arrayOfCubes[lineCounter])->sfy = f;
				 ((Cube*)arrayOfCubes[lineCounter])->sfz = g;
				 lineCounter++;
			 }

			 fclose(fileToOpen);
		 }
		break;
	}
	glutPostRedisplay();
}

void functionKeys(int key, int x, int y)
{
	float spin = 0.0;
	if (key == GLUT_KEY_F1)
	{
		// Create and initialize new cube
		// add to your array see cube.h
		//printf("add one more");
		//arrayOfCubes[0] = createCube();
		for (int i = 0; i < 100; i++){
			if (arrayOfCubes[i] == NULL) {
			arrayOfCubes[i] = (Cube*)calloc(1, sizeof(Cube));
			arrayOfCubes[i] = createCube();
			break;
			}
		}
	}
	
	// Arrow keys
	switch(key)
	{
	case GLUT_KEY_DOWN:
		for (int i = 0; i < 100; i++){
			if (arrayOfCubes[i] != NULL && arrayOfCubes[i]->selected == true){
				if (mode == 1){
					backward(arrayOfCubes[i]);
				}
				if (mode == 2){
					zIncrease(arrayOfCubes[i]);
				}
				if (mode == 4){
					shrinkHeight(arrayOfCubes[i]);
				}
			}
		}
	break;
	case GLUT_KEY_UP:
		for (int i = 0; i < 100; i++){
			if (arrayOfCubes[i] != NULL && arrayOfCubes[i]->selected == true){
			if (mode == 1){
				forward(arrayOfCubes[i]);
			}
			if (mode == 2){
				zDecrease(arrayOfCubes[i]);
			}
			if (mode == 4){
				growHeight(arrayOfCubes[i]);
			}
		}
		}
	break;
	case GLUT_KEY_RIGHT:
		if (mode == 5 && !multipleSelect){
			((Cube*)arrayOfCubes[abs(selected)])->selected = false;
			selected = ((selected + 1) % currentActiveSizeOfCubeArray());
			((Cube*)arrayOfCubes[abs(selected)])->selected = true;
		}
		if (mode == 6){
			selected = ((selected + 1) % currentActiveSizeOfCubeArray());
			((Cube*)arrayOfCubes[abs(selected)])->selected = true;
		}
		for (int i = 0; i < 100; i++){
			if (arrayOfCubes[i] != NULL && arrayOfCubes[i]->selected == true){
				if (mode == 1){
					//printf("i am pressing right");
					right(arrayOfCubes[i]);
				}
				if (mode == 2){
					xIncrease(arrayOfCubes[i]);
				}
				if (mode == 3){
					spinRight(arrayOfCubes[i]);
				}
			}
		}

	break;
	case GLUT_KEY_LEFT:
		if (mode == 5 && !multipleSelect){
			((Cube*)arrayOfCubes[abs(selected)])->selected = false;
			selected = ((selected - 1) % currentActiveSizeOfCubeArray());
			((Cube*)arrayOfCubes[abs(selected)])->selected = true;
		}
		if (mode == 6){
			selected = ((selected - 1) % currentActiveSizeOfCubeArray());
			((Cube*)arrayOfCubes[abs(selected)])->selected = true;
		}
		for (int i = 0; i < 100; i++){
			if (arrayOfCubes[i] != NULL && arrayOfCubes[i]->selected == true){
				if (mode == 1){
					//printf("i am pressing left");
					left(arrayOfCubes[i]);
				}
				if (mode == 2){
					xDecrease(arrayOfCubes[i]);
				}
				if (mode == 3){
					spinLeft(arrayOfCubes[i]);
				}
			}
		}

	break;
	default:
	break;
	}

	glutPostRedisplay();
}

int currentActiveSizeOfCubeArray(){
	int currentSize = 0;
	for (int i = 0; i < 100; i++){
		if (arrayOfCubes[i] != NULL){
			currentSize++;
		}
		else if (arrayOfCubes[i] == NULL){
			break;
		}
	}
	return currentSize;
}
