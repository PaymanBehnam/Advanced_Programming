/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .h for Ghost. 
1. Each ghost needs to run in it’s own thread
2. Each ghost needs to continuously determine the path to pursue pac-man.
3. Ghost can be made with a sphere for a head and cylinder for body
4. Each ghost needs to have a unique color
a. Red, green, orange, pink
5. Ghost’s motion must be restricted by maze walls.
6. The ghost need to use a shortest path algorithm to determine the path towards pac-man. 
Texture is disabled for the ghosts. 
*/
#include <iostream>
#include <GL/glut.h> // on linux
//#include <GLUT/glut.h> //on MAC
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ECE_Ghost.h"
#include "ECE_Pacman.h"
#include "maze.h"

extern unsigned int ghost_eye_tex;

//Constructor
ECE_Ghost::ECE_Ghost(color ghostCol) {
	ghostColor = ghostCol;
	radius = 0.06;
	height = 0.08;
	dirX = 0;
	dirY = 0;
	zCoord = 0;
	speed = 0.2;
	started = false;
	chase = true;
	dead = false;
}
//set location of the ghost by x, and u
void ECE_Ghost::setLoc(float x, float y) {
	xLoc = x;
	yLoc = y;
	row = round(yLoc);
	col = round(xLoc);
	xCoord = toWorldX(xLoc);
	yCoord = toWorldY(yLoc);
}
//we can use set the pacman as we make an object of pacman in ghost.
void ECE_Ghost::setPacman(ECE_Pacman *p) {
	pacman = p;
}

// getter for row in maze
int ECE_Ghost::getRow() {
	return row;
}

// getter for column in maze
int ECE_Ghost::getCol() {
	return col;
}

// move ghost
void ECE_Ghost::move()
{
	if (!started) {
		return;
	}

	// update position of ghost
	updatePosition(&xLoc, &yLoc, dirX, dirY, speed);

	// get position in world space for drawing
	xCoord = toWorldX(xLoc);
	yCoord = toWorldY(yLoc);

	row = round(yLoc);
	col = round(xLoc);

	/* update direction */

	if (chase) {  // chasing pacman
		int min = rowNo * colNo;

		// search the cell with the shortest path to pacman around the current position
		if (row + 1 < rowNo && pacman->stepCount(row + 1, col) < min) {
			dirX = 0; dirY = 1;
			min = pacman->stepCount(row + 1, col);
		}

		if (row - 1 > -1 && pacman->stepCount(row - 1, col) < min) {
			dirX = 0; dirY = -1;
			min = pacman->stepCount(row - 1, col);
		}

		if (col + 1 < colNo && pacman->stepCount(row, col + 1) < min) {
			dirX = 1; dirY = 0;
			min = pacman->stepCount(row, col + 1);
		}

		if (col - 1 > -1 && pacman->stepCount(row, col - 1) < min) {
			dirX = -1; dirY = 0;
			min = pacman->stepCount(row, col - 1);
		}

	} else {  // running away from pacman
		int max = 0;

		// search the cell with the longest path to pacman around the current position
		if (maze[row + 1][col] !=3 && row + 1 < rowNo && pacman->stepCount(row + 1, col) > max) {
			dirX = 0; dirY = 1;
			max = pacman->stepCount(row + 1, col);
		}

		if (maze[row - 1][col] !=3 && row - 1 > -1 && pacman->stepCount(row - 1, col) > max) {
			dirX = 0; dirY = -1;
			max = pacman->stepCount(row - 1, col);
		}

		if (maze[row][col + 1] !=3 && col + 1 < colNo && pacman->stepCount(row, col + 1) > max) {
			dirX = 1; dirY = 0;
			max = pacman->stepCount(row, col + 1);
		}

		if (maze[row][col - 1] !=3 && col - 1 > -1 && pacman->stepCount(row, col - 1) > max) {
			dirX = -1; dirY = 0;
			max = pacman->stepCount(row, col - 1);
		}
	}
}

// This function draws the ghost with the correct texture and the eyes facing the correct direction
void ECE_Ghost::draw(GLUquadricObj* quadratic) {
	if (dead) {
		return;
	}

	//The glPushMatrix and glPopMatrix functions push and pop the current matrix stack. it used to specify where we are.
	glPushMatrix();

	if (chase) {
		switch (ghostColor) {
		case RED:
			glColor3f(1.0, 0.0, 0.0);
			break;
		case PINK:
			glColor3f(1.0, 0.4, 0.8);
			break;
		case GREEN:
			glColor3f(0.0, 1.0, 0.0);
			break;
		case ORANGE:
			glColor3f(1.0, 0.82, 0.09);
			break;
		}
	} else {
		glColor3f(1.0, 1.0, 1.0);
	}

	////we end up being in a specific cordinate
	glPopMatrix();
	glPushMatrix();
	///These functions multiply the current matrix by a translation matrix to move an object
	glTranslatef(xCoord * blockStep, yCoord * blockStep, zCoord * blockStep + height);
	//draw sphere
	glutSolidSphere((GLfloat)radius, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(xCoord * blockStep, yCoord * blockStep, zCoord * blockStep);
	//draw cylinder
	gluCylinder(quadratic, (GLfloat)radius, (GLfloat)radius, (GLfloat)height, 32, 32);
	glPopMatrix();
	glPushMatrix();
	//drawEye();
	glPopMatrix();
}


//Draws the texture passed in given the height, length
/*
void ECE_Ghost::drawTexture(unsigned int texture)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);   // Set background colour to white. This should never be seen but allows a visual debug to see if a texture hasn't
									// been loaded or bound correctly.
	float widthCentre = radius;
	float verticalCentre = radius;
	// Translate to center of object to rotate about its origin
	glTranslatef(xCoord, yCoord, zCoord + height);
	//glRotatef(20, 1.0f, 0.0f, 0.0f); // Rotate
	// Enable texturing and bind the specific object
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Specify texture coordinates
	//glBegin and glEnd delimit the vertices that define a primitive or a group of like primitives. glBegin accepts a single argument that specifies in which of ten ways the vertices are interpreted.
	//Draws a connected group of quadrilaterals. One quadrilateral is defined for each pair of vertices presented after the first pair. Vertices 2 â¢ n - 1 , 2 â¢ n , 2 â¢ n + 2 , and 2 â¢ n + 1 define quadrilateral n. N 2 - 1 quadrilaterals are drawn. Note that the order in which vertices are used to construct a quadrilateral from strip data is different from that used with independent data.
	glTexCoord2f(0.0f, 0.0f);      // Lower left corner
	glVertex2f(-widthCentre, -verticalCentre);
	glTexCoord2f(1.0f, 0.0f);      // Lower right corner
	glVertex2f(widthCentre, -verticalCentre);
	glTexCoord2f(1.0f, 1.0f);      // Upper right corner
	glVertex2f(widthCentre, verticalCentre);
	glTexCoord2f(0.0f, 1.0f);      // Upper left corner
	glVertex2f(-widthCentre, verticalCentre);
	glDisable(GL_TEXTURE_2D);
	// Pop matrix to ignore above transformations on future objects
	glPopMatrix();
}
*/
/*
//add eye texture to ghost
void ECE_Ghost::drawEye() {
	glPushMatrix();
	//unsigned int ghost_eye_tex;
	glEnable(GL_BLEND);
	//Transparency is best implemented using blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest. Note that this transparency calculation does not require the presence of alpha bitplanes in the frame buffer.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawTexture(ghost_eye_tex);
	glPopMatrix();
}

*/