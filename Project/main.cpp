/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .cpp for main function where we can dsiplay the game. We put all things together, use arrow keys to control the movement of pacman and handle moving objects properly. 
*/

#include <stdio.h>
#include <stdlib.h>
// #include <Windows.h>
//#include <GL/glut.h>
#include <GLUT/glut.h> //on MAC
#include <math.h>
#include <iostream>
#include <thread>
#include "Utility.h" //// several useful function especially used in texture mapping are defined here

#include "ECE_Ghost.h"
#include "ECE_Pacman.h"
#include "maze.h"
#include "game_control.h"


static int ang = 45;// 0; //global varibale
static int interval = 30;  // frame length in milisecond
static GameControl gameControl = GameControl();

GLUquadricObj* quadratic = { nullptr };

//Define Ghost variables
ECE_Ghost ghosts[4] = {
	ECE_Ghost(RED),
	ECE_Ghost(PINK),
	ECE_Ghost(ORANGE),
	ECE_Ghost(GREEN)
};

ECE_Pacman pacman; //make an object

 unsigned int ghost_eye_tex, pac_tex; //define varible used for texture mapping


///////////////////////////////////////////////////////////////////////////
// Load and bind all textures at once to save performance as all only need to be load and bound once at the beginning during initialization
void loadAndBindTextures()
{
	// Enable blending so textures can be transparent
	glEnable(GL_BLEND);
	//Specifies how the red, green, blue, and alpha source blending factors are computed.
	//Transparency is best implemented using blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest. Note that this transparency calculation does not require the presence of alpha bitplanes in the frame buffer.
	//https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glBlendFunc.xml
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind ghost eye textures
	ghost_eye_tex = load_and_bind_texture("Images/eyes/down.png");

	// Bind Pacman texture
	pac_tex = load_and_bind_texture("Images/pacman/mypacman.png");
}


////////////Initilize drawing ///////////////////////////////////////////////////////////////

void init(void)
{
	// Specifies clear values for the color buffers.
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);  // Selects mooth shading to make object more soft.

	if (!quadratic) {  // make sure it is not null/
		quadratic = gluNewQuadric();
	}

	gameControl.setGhosts(ghosts);
	gameControl.setPacman(&pacman);

	for (int i = 0; i < 4; i++) {
		ghosts[i].setPacman(&pacman);
	}

	gameControl.initPosition();

	// loadAndBindTextures();
}

void display(void)
{
	// Clear frame buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/////////////////////////////////////////////////////////////////////////////
	//source : https://www.khronos.org/opengl/wiki/How_lighting_works & https://www.glprogramming.com/red/chapter05.html
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	//enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL); //Enabling the state GL_COLOR_MATERIAL causes the material color to track the current color for the face you specif
	//The number of lights depends on the implementation, but at least eight lights are supported. They are identified by symbolic names of the form GL_LIGHT i, where i ranges from 0 to the value of GL_MAX_LIGHTS - 1.
	glEnable(GL_LIGHT0);
	////////////////////////////////////////////////////////////////////////

	GLfloat clrBlue[] = { 0.0f, 0.5f, 1.0f, 1.0f };
	GLfloat clrSilver[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	// Change the color and light reflection to light blue
	glColor3fv(clrBlue); //set the coler RGB

	//The glMaterialf function specifies material parameters for the lighting model.
	//The glMaterialfv function specifies material parameters for the lighting model.
	//Ambinet:The params parameter contains four floating-point values that specify the ambient RGBA intensity of the light. Floating-point values are mapped directly. Neither integer nor floating-point values are clamped. The default ambient light intensity is (0.0, 0.0, 0.0, 1.0).
	glMaterialfv(GL_FRONT, GL_AMBIENT, clrBlue);
	//Diffue: The params parameter contains four floating-point values that specify the diffuse RGBA intensity of the light. Floating-point values are mapped directly. Neither integer nor floating-point values are clamped. The default diffuse intensity is (0.0, 0.0, 0.0, 1.0) for all lights other than light zero. The default diffuse intensity of light zero is (1.0, 1.0, 1.0, 1.0).
	glMaterialfv(GL_FRONT, GL_DIFFUSE, clrBlue);
	// Change the specular reflection color to silver
	//specular:The params parameter contains four floating-point values that specify the specular RGBA intensity of the light. Floating-point values are mapped directly. Neither integer nor floating-point values are clamped. The default specular intensity is (0.0, 0.0, 0.0, 1.0) for all lights other than light zero. The default specular intensity of light zero is (1.0, 1.0, 1.0, 1.0).
	glMaterialfv(GL_FRONT, GL_SPECULAR, clrSilver);
	// Set the shininess to medium for glossy plastic look
	glMaterialf(GL_FRONT, GL_SHININESS, 64);

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	/////////////////////////////////////////////////////////////////////////////

    // Set up viewing transformation, looking down -Z axis
	///glLoadIdentity replaces the current matrix with the identity matrix. It is semantically equivalent to calling glLoadMatrix with the identity matrix
	//1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1, but in some cases it is more efficient.

	glLoadIdentity();

	//gluPerspective( /* field of view in degree */ 0.0,   /* aspect ratio */ 1.0,    /* Z near */ 10.0, /* Z far */ 1.0);
	//   gluPerspective( /* field of view in degree */ 40.0,   /* aspect ratio */ 1.0,    /* Z near */ 1.0, /* Z far */ 10.0);


	//gluLookAt creates a viewing matrix derived from an eye point, a reference point indicating the center of the scene, and an UP vector.
	//The matrix maps the reference point to the negative z axis and the eye point to the origin. When a typical projection matrix is used, the center of the scene therefore maps to the center of the viewport. Similarly, the direction described by the UP vector projected onto the viewing plane is mapped to the positive y axis so that it points upward in the viewport.
	//where we look at, where the object is and what is the up vector/

	gluLookAt(15, -3, 7, 0, 0, 0, 0, 0, 1);
	//make a rotation based on ang in the keyboard function. roataion happens over z. by chanigine 0 to 1 , rotation can happen over other axes.
	glRotatef((GLfloat)ang, 0.0f, 0.0f, 1.0f);

	//gluLookAt(6, -6, 4, 0, 0, 0, 0, 0, 1);

	 //scale the object
	glScalef(1.8, 1.8, 1.8);

	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	//glTranslatef(-2.6, 2.6, -2);
	glTranslatef(-2, 2.5, -1);

	//Draw maze
	glPushMatrix();
	// Change the color and light reflection to light blue
	glColor3fv(clrBlue);
	glMaterialfv(GL_FRONT, GL_AMBIENT, clrBlue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, clrBlue);
	// Change the specular reflection color to silver
	glMaterialfv(GL_FRONT, GL_SPECULAR, clrSilver);
	// Set the shininess to medium for glossy plastic look
	glMaterialf(GL_FRONT, GL_SHININESS, 64);

	drawMaze(quadratic, blockStep);
	glPopMatrix();

	for (int i = 0; i < rowNo; i++) {
		for (int j = 0; j < colNo; j++) {
			if (maze[i][j] == 1)
				drawCoin(blockStep*(j + 1), blockStep*(-i - 1), 0);
			if (maze[i][j] == 2)
				drawGoldenDisk(quadratic, blockStep*(j + 1), blockStep*(-i - 1), 0);
		}
	}
	// Putting pacman in the maze
	//CHANGE: pacman move based on its coordinate:
	pacman.draw();
	// Putting ghosts in the maze
	ghosts[0].draw(quadratic);
	ghosts[1].draw(quadratic);
	ghosts[2].draw(quadratic);
	ghosts[3].draw(quadratic);

	gameControl.drawText();

	glPopMatrix();
	// Performs a buffer swap on the layer in use for the current window. Specifically, glutSwapBuffers promotes the contents of the back buffer of the layer in use of the current window to become the contents of the front buffer. The contents of the back buffer then become undefined. The update typically takes place during the vertical retrace of the monitor, rather than immediately after glutSwapBuffers is called.
	glutSwapBuffers();
}


/////////////////////to create reshape property of an object. reshaping can be propotional//////////////////////////////////////////////////////////
void reshape(int w, int h)
{
	//glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates. Let x nd y nd be normalized device coordinates. Then the window coordinates x w y w are computed as follows:
	//x w = x nd + 1 â¢ width 2 + x y w = y nd + 1 â¢ height 2 + y
	//Viewport width and height are silently clamped to a range that depends on the implementation.
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, (GLfloat)w / (GLfloat)h, 1.0, 30.0);
	//glMatrixMode sets the current matrix mode. mode can assume one of four values:
	//GL_MODELVIEW:Applies subsequent matrix operations to the modelview matrix stack.
	//GL_PROJECTION: Applies subsequent matrix operations to the projection matrix stack.

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

//Make rotation with R or r. Rotation can happen on x, y or z. I just pick one.
void keyboard(unsigned char key, int x, int y)
{
	gameControl.start();

	switch (key) {
	case 'R':
	case 'r':
		ang = (ang + 5) % 360; //360 is one full circulation
		glutPostRedisplay(); //redraw after rotation
		break;
	default:
		break;
	}
}

/*
 * arrow key function for control packman direction of movement
 */
void specKey(int key, int x, int y)
{
	gameControl.start();

	switch (key) {
	case GLUT_KEY_UP:
		pacman.setDir(0, -1);
		break;
	case GLUT_KEY_DOWN:
		pacman.setDir(0, 1);
		break;
	case GLUT_KEY_LEFT:
		pacman.setDir(-1, 0);
		break;
	case GLUT_KEY_RIGHT:
		pacman.setDir(1, 0);
		break;
	default:
		break;
	}
}
///// handeling ghost move
void moveGhost(uint index) {
	ghosts[index].move();
}
////// handeling ghost and pacman moves by calling moveGhost and handle in using thread and pacman move by calling  pacman.move();
void moveObjects(int value)
{
	if (gameControl.ended) {
		return;
	}
	// 	handeling pacmanmove move 
	pacman.move();
	//	handeling ghost move  by threads. 
	for (int i = 0; i < 4; i++) {
		std::thread t(&moveGhost, i);
		t.join();
	}
	//Mark the normal plane of current window as needing to be redisplayed. The next iteration through glutMainLoop, 
	//the window's display callback will be called to redisplay the window's normal plane. 
	glutPostRedisplay();
	//glutTimerFunc invokes a certain function (moveObjects) after a certain duration
	////glutTimerFunc registers the timer callback func to be triggered in at least msecs milliseconds. 
	//The value parameter to the timer callback will be the value of the value parameter to glutTimerFunc.
	//pacman move is done in the main thread
	//And ghost move is done in its own thread
	glutTimerFunc(interval, moveObjects, 0);

	//	void update(int delta);  // update game process with interval in milisecond!check the status of game including if to finish game or not! Checking if pacman consumes powerup and coins
	gameControl.update(interval);
}

int main(int argc, char** argv)
{
	//They're used so that GLUT can process command line arguments. It has a number of arguments that it always uses. If you don't want GLUT to process arguments, just pass something

	glutInit(&argc, argv);
	// glutInitDisplayMode sets the initial display mode.
	// GLUT_DOUBLE:Bit mask to select a double buffered window. This overrides GLUT_SINGLE if it is also specified.
	// GLUT_DEPTH: Bit mask to select a window with a depth buffer.
	// GLUT_RGBA: Bit mask to select an RGBA mode window. This is the default if neither GLUT_RGBA nor GLUT_INDEX are specified.
	// GLUT_RGB: An alias for GLUT_RGBA.
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	// Windows created by glutCreateWindow will be requested to be created with the current initial window position and size.
	glutInitWindowSize(1000, 500);
	// This function allows you to request an initial position for future windows.
	glutInitWindowPosition(100, 50);
	// glutCreateWindow creates a top-level window. The name will be provided to the window system as the window's name. The intent is that the window system will label the window with the name. Implicitly, the current window is set to the newly created window.
	glutCreateWindow(argv[0]);
	// glutDisplayFunc sets the display callback for the current window.
	glutDisplayFunc(display);
	// glutReshapeFunc sets the reshape callback for the current window.
	glutReshapeFunc(reshape);
	// glutKeyboardFunc sets the keyboard callback for the current window. When a user types into the window, each key press generating an ASCII character will generate a keyboard callback. The key callback parameter is the generated ASCII character.
	glutKeyboardFunc(keyboard);
	// NEW: special key function for arrow keys
	glutSpecialFunc(specKey);
	// NEW: it is a function that run continiously and move pacman based on pressed arrow key;
	glutTimerFunc(interval, moveObjects, 0);

	// initialize settings
	init();

	// glutMainLoop enters the GLUT event processing loop. This routine should be called at most once in a GLUT program. Once called, this routine will never return. It will call as necessary any callbacks that have been registered.
	glutMainLoop();
	// gluDeleteQuadric destroys the quadrics object (created with gluNewQuadric) and frees any memory it uses. Once gluDeleteQuadric has been called, quad cannot be used again.
	gluDeleteQuadric(quadratic);
	return 0;
}
