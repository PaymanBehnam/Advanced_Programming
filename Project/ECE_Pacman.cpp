/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .cpp for Pacman. 
1-Pac-man can be drawn as a yellow sphere
2. Pac-main is controlled in the main thread using the
a. Left, right, up, down arrow keys to change pac-man’s direction
Texture of pacman is disabeled for final. 
*/

// #include <Windows.h>
//#include <GL/glut.h> // on linux
#include <GLUT/glut.h> //on MAC
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "maze.h"
#include "ECE_Pacman.h"

extern unsigned int pac_tex;

//constuctor
ECE_Pacman::ECE_Pacman()
{
	radius = 0.06;
	zCoord = 0.0;
	dirX = 0;
	dirY = 0;
	speed = 0.15;
}

// update the map of the shortest steps to each cell from pacman
void ECE_Pacman::updatePathMap() {

	// minimum steps to each cell is initialized with maximum value
	for (int i = 0; i < rowNo; i++) {
		for (int j = 0; j < colNo; j++) {
			pathMap[i][j] = rowNo * colNo;
		}
	}

	// steps to the current position of pacman is initialized with 0
	pathMap[row][col] = 0;

	// calculate the minimum steps to each cell
	for (int repeat = 0; repeat < rowNo * colNo; repeat++) {
		for (int i = 0; i < rowNo; i++) {
			for (int j = 0; j < colNo; j++) {
				if (maze[i][j] == 3) {
					continue;
				}

				// if the steps of a neighbor cell plus one step is smaller than the current step
				// update it

				if (i + 1 < rowNo && maze[i + 1][j] != 3 && pathMap[i][j] > pathMap[i + 1][j] + 1) {
					pathMap[i][j] = pathMap[i + 1][j] + 1;
				}
				if (i - 1 > -1 && maze[i - 1][j] != 3 && pathMap[i][j] > pathMap[i - 1][j] + 1) {
					pathMap[i][j] = pathMap[i - 1][j] + 1;
				}
				if (j + 1 < colNo && maze[i][j + 1] != 3 && pathMap[i][j] > pathMap[i][j + 1] + 1) {
					pathMap[i][j] = pathMap[i][j + 1] + 1;
				}
				if (j - 1 > -1 && maze[i][j - 1] != 3 && pathMap[i][j] > pathMap[i][j - 1] + 1) {
					pathMap[i][j] = pathMap[i][j - 1] + 1;
				}
			}
		}
	}
}

// getter for steps to the cell (row, col)
int ECE_Pacman::stepCount(int row, int col) {
	return pathMap[row][col];
}

//setter functions
void ECE_Pacman::setLoc(float x, float y) {
	xLoc = x;
	yLoc = y;
	xCoord = toWorldX(xLoc);
	yCoord = toWorldY(yLoc);

	row = round(yLoc);
	col = round(xLoc);

	updatePathMap();
}
//Set direction for pacman
void ECE_Pacman::setDir(int x, int y) {

	// if new position is outside maze, then return
	if (row + y > rowNo - 1 || row + y < 0 || col + x > colNo - 1 || col + x < 0) {
		return;
	}

	// if new position is wall, then return
	if (maze[row + y][col + x] == 3) {
		return;
	}

	dirX = x;
	dirY = y;
}
//get Row of Pacman
int ECE_Pacman::getRow() {
	return row;
}
//get Col of Pacman
int ECE_Pacman::getCol() {
	return col;
}

// move function
void ECE_Pacman::move()
{
	// update position of pacman
	updatePosition(&xLoc, &yLoc, dirX, dirY, speed, false);
	xCoord = toWorldX(xLoc);
	yCoord = toWorldY(yLoc);

	// update the map of shortest path
	if (round(xLoc) != col || round(yLoc) != row) {
		row = round(yLoc);
		col = round(xLoc);
		updatePathMap();
	}
}

//Draw pacman
////////////////////////////////////////////////////////////////////
void ECE_Pacman::draw()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(blockStep * xCoord, blockStep * yCoord, blockStep * zCoord);
	glutSolidSphere(radius, 300, 300);
	glPopMatrix();
	glPushMatrix();
	//drawFace(); // texture of the pacman : moth and eyes. used in lab4
	glPopMatrix();
}
//texture for pacman has been disabled in this lab!
///////////////////////////////////////////////////////////////////////
//Draws the texture passed in given the height, length
/*
void ECE_Pacman::drawTexture(unsigned int texture)
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);   // Set background colour to white. This should never be seen but allows a visual debug to see if a texture hasn't
									// been loaded or bound correctly.
	float widthCentre = radius;
	float verticalCentre = radius;
	// Translate to center of object to rotate about its origin
	glTranslatef(xCoord, yCoord, zCoord);
	//glRotatef(20, 1.0f, 0.0f, 0.0f); // Rotate
	// Enable texturing and bind the specific object
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Specify texture coordinates
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
//texture mappping for adding face to Mr. Packman
/*
void ECE_Pacman::drawFace()
{
	glPushMatrix();
	glEnable(GL_BLEND);
	//Transparency is best implemented using blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest. Note that this transparency calculation does not require the presence of alpha bitplanes in the frame buffer.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawTexture(pac_tex);
	glPopMatrix();
}
*/
