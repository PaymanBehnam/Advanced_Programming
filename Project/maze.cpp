/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .cpp for objects you see and happens in maze. 
*/
#ifndef MAZE
#define MAZE

// #include <Windows.h>
//#include <GL/glut.h>
#include <GLUT/glut.h> //on MAC

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

double blockStep = 0.15;

int rowNo = 20;  // define number of rows
int colNo = 17;  // define number of columns
/**
 *      0: Ghost, Pacman
 *      1: Coin
 *      2: Power up golden flat disc
 *      3: wall
 *		4: empty
 */
 // 2D array defines the size of the maze and also what each tile contains
int maze[20][17] =
{	    {1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1},
		{2,3,3,1,3,3,3,1,3,1,3,3,3,1,3,3,2},
		{1,3,3,1,3,3,3,1,3,1,3,3,3,1,3,3,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,3,3,1,3,1,3,3,3,3,3,1,3,1,3,3,1},
		{1,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,1},
		{3,3,3,1,3,3,3,4,3,4,3,3,3,1,3,3,3},
		{4,4,3,1,3,4,4,4,4,4,4,4,3,1,3,4,4},
		{3,3,3,1,3,4,3,3,5,3,3,4,3,1,3,3,3},
		{4,4,4,1,4,4,3,5,5,5,3,4,4,1,4,4,4},
		{3,3,3,1,3,4,3,3,3,3,3,4,3,1,3,3,3},
		{4,4,3,1,3,4,4,4,4,4,4,4,3,1,3,4,4},
		{3,3,3,1,3,4,3,3,3,3,3,4,3,1,3,3,3},
		{1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1},
		{1,3,3,1,3,3,3,1,3,1,3,3,3,1,3,3,1},
		{2,1,3,1,1,1,1,1,4,1,1,1,1,1,3,1,2},
		{3,1,3,1,3,1,3,3,3,3,3,1,3,1,3,1,3},
		{1,1,1,1,3,1,1,1,3,1,1,1,3,1,1,1,1},
		{1,3,3,3,3,3,3,1,3,1,3,3,3,3,3,3,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int ghostMap[20][17] = {{0}};

// calculate x coordinate in maze
float toWorldX(float x) {
	return x + 1;
}

// calculate y coordinate in maze
float toWorldY(float y) {
	return -(y + 1);
}


// update position of pacman or ghosts
void updatePosition(float *x, float *y, int dirX, int dirY, float speed, bool ghost) {
	// get new coordinates
	float newX = *x + speed * dirX;
	float newY = *y + speed * dirY;

	// get row and column in maze
	int newRow = (int)round(*y) + dirY;
	int newCol = (int)round(*x) + dirX;

	// if new position crosses the boundaries of the maze, no update

	if (ghost && maze[(int)round(*y)][(int)round(*x)] != 5 && maze[newRow][newCol] == 5) {
		return;
	}

	if (ghost && ghostMap[newRow][newCol] == 1) {
		return;
	}

	if (newRow > rowNo - 1 && newY > rowNo - 1) {
		return;
	}

	if (newRow < 0 && newY < 0) {
		return;
	}

	if (newCol > colNo - 1 && newX > colNo - 1) {
		// be able to escape to the right hole of the maze
		if (newRow == 9) {
			newCol = 0;
			newX = -0.5;
		} else {
			return;
		}
	}

	if (newCol < 0 && newX < 0) {
		// be able to escape to the left hole of the maze
		if (newRow == 9) {
			newCol = colNo - 1;
			newX = colNo - 0.5;
		} else {
			return;
		}

	}

	// if the new position is on wall, no update
	if (maze[newRow][newCol] == 3) {
		if (
			(dirX == -1 && newX < newCol + 1) ||
		 	(dirX == 1 && newX > newCol - 1) ||
		 	(dirY == -1 && newY < newRow + 1) ||
		 	(dirY == 1 && newY > newRow - 1)
		) {
			return;
		}
	}

	*x = newX;
	*y = newY;
}

// draw silver coin
void drawCoin(float xCoord, float yCoord, float zCoord) {
	glPushMatrix();
	glColor3ub(192, 192, 192); //silver color
	glTranslatef(xCoord, yCoord, zCoord);
	glutSolidSphere(0.02, 32, 32); //draw sphere
	glPopMatrix();

}
///////////////////// draw gold coin///////////////////////////////////////////////////////////////
/*void drawGoldenDisk(GLUquadricObj* quadratic, float xCoord, float yCoord, float zCoord){
   glPushMatrix();
		glColor3ub(212, 175, 55); ////specify the gold color. GLubyte red,GLubyte green,GLubyte blue)
		glTranslatef(xCoord,yCoord,zCoord);
		gluDisk(quadratic, 0, 0.04f, 1024, 1024); //draw disck
	glPopMatrix();
}*/
//different way of draw gold coin
void drawGoldenDisk(GLUquadricObj* quadratic, float xCoord, float yCoord, float zCoord) {
	glPushMatrix();
	glColor3ub(212, 175, 55); /////specify the gold color. GLubyte red,GLubyte green,GLubyte blue)
	//glTranslatef(xCoord,yCoord,zCoord);
	glPushMatrix();
	glTranslatef(xCoord, yCoord, zCoord);
	// Place a cylinder as the base of the coin
	gluCylinder(quadratic, 0.04, 0.04, 0.02, 16, 16);
	glPopMatrix();
	glPushMatrix();
	// Place a circular disk on top the base cylinder
	glTranslatef(xCoord, yCoord, zCoord + 0.02);
	gluDisk(quadratic, 0, 0.04f, 32, 32); //draw disk
	glPopMatrix();
	glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////draw the maze by segmentation, push and pup//////////////////////////////////////////////////
void drawMaze(GLUquadricObj* quadratic, double blockStep) {
	GLfloat radius = 0.02f;  // thin cylinder
// Create side walls/////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(0, 0, 0); //shifting. origin: no shift
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //rotating
	gluCylinder(quadratic, radius, radius, blockStep * 18, 32, 32); //draw wall (cylinder)
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 7, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, blockStep*(-7), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 3, blockStep*(-7), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, blockStep*(-9), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, blockStep*(-11), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 3, blockStep*(-11), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, blockStep*(-13), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, blockStep*(-13), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 8, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, blockStep*(-21), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 18, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 18, blockStep*(-13), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 8, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-13), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-11), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-11), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-9), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-7), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-7), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 18, 0, 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 7, 32, 32);
	glPopMatrix();
	// End side walls/////////////////////////////////////////////////////
	//Upper-left small square with size of 1*1 /////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 2, blockStep*(-2), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 2, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 2, blockStep*(-3), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 3, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//Upper-left medium rectangle with size of 1*2 /////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-2), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-3), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 7, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//Upper-right medium rectangle with size of 1*2 /////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 11, blockStep*(-2), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 11, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 11, blockStep*(-3), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 13, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//Upper-right small square with size of 1*1 /////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-2), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-3), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 16, blockStep*(-2), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//central big rectangle with size of 2*4 /////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 7, blockStep*(-9), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 7, blockStep*(-9), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 7, blockStep*(-11), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 11, blockStep*(-9), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// vertical line that seperates upper left and upper right sections //////
	glPushMatrix();
	glTranslatef(blockStep * 9, 0, 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 3, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Horizontal and vertical lines that seperate upper left and upper right sections //////
	glPushMatrix();
	glTranslatef(blockStep * 7, blockStep*(-5), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 9, blockStep*(-5), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Small horizontal lines in both left and right sides in the upper section
	glPushMatrix();
	glTranslatef(blockStep * 2, blockStep*(-5), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-5), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Vertical & horizontal lines in both upper left and upper right sides of central rectangle
	// Upper-Left of central rectangle //////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-5), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-7), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	// Upper-Right of central rectangle //////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 13, blockStep*(-5), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 11, blockStep*(-7), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Small vertical lines in both lower-left and lower-right sides of central rectangle
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-11), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 13, blockStep*(-11), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Two Horizontal-vertical-lines in the below section of central rectangle (The initial position of Pacman)
	//Upper //////////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 7, blockStep*(-13), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 9, blockStep*(-13), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//Lower //////////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 7, blockStep*(-17), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 9, blockStep*(-17), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Small horizontal lines in both left and right sides of initial positoin of Pacman
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-15), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 11, blockStep*(-15), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Small horizontal lines in both lower-left and lower-right sides of maze
	glPushMatrix();
	glTranslatef(0, blockStep*(-17), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 17, blockStep*(-17), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Two Horizontal-vertical-lines in both left and right sides of initial position of Pacman
	//Left //////////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 2, blockStep*(-15), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 3, blockStep*(-15), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//Right //////////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-15), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 15, blockStep*(-15), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Two Big-vertical-Small-Horizontal-lines in both lower-left and lower-right sides of the maze
	//Left /////////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 5, blockStep*(-17), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 2, blockStep*(-19), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 5, 32, 32);
	glPopMatrix();
	//Right //////////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(blockStep * 13, blockStep*(-17), 0);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(blockStep * 11, blockStep*(-19), 0);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, radius, radius, blockStep * 5, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
}

/* The other way of drawing cylinder. however I didnt use it finally.
void draw_cylinder(GLfloat radius, GLfloat height)
{
	glPushMatrix(); //

	radius = 0.02f;  // thin cylinder

	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;
	// Draw the tube
	//glColor3ub(R-40,G-40,B-40);
	glColor3f(0.0,0.0,1.0); // set the color to blue!
	//glBegin and glEnd delimit the vertices that define a primitive or a group of like primitives. glBegin accepts a single argument that specifies in which of ten ways the vertices are interpreted.
	//Draws a connected group of quadrilaterals. One quadrilateral is defined for each pair of vertices presented after the first pair. Vertices 2 â¢ n - 1 , 2 â¢ n , 2 â¢ n + 2 , and 2 â¢ n + 1 define quadrilateral n. N 2 - 1 quadrilaterals are drawn. Note that the order in which vertices are used to construct a quadrilateral from strip data is different from that used with independent data.
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while( angle < 2*PI ) { //traverese the pyramic
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y , height); //Specifies a vertex.
		glVertex3f(x, y , 0.0);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glVertex3f(radius, 0.0, 0.0);
	glEnd();
	// Draw the circle on top of cylinder
	//glColor3ub(R,G,B);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON); //Draws a single, convex polygon. Vertices 1 through N define this polygon.

	angle = 0.0;
	while( angle < 2*PI ) {
		x = radius * cos(angle);
		y = radius * sin(angle);
		glVertex3f(x, y , height);
		angle = angle + angle_stepsize;
	}
	glVertex3f(radius, 0.0, height);
	glEnd();

   // Pop matrix to ignore above transformations on future objects
	glPopMatrix();

}
*/
#endif // MAZE
