/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .h for objects you see and happens in maze. 
*/
#pragma once

#ifndef MAZE
#define MAZE

#include <GL/glut.h>
//#include <GLUT/glut.h> //on MAC


extern double blockStep;

extern int rowNo;  // define number of rows
extern int colNo;  // define number of columns

// 2D array defines the size of the maze and also what each tile contains
extern int maze[20][17];

// draw silver coin
void drawCoin(float xCoord, float yCoord, float zCoord);

// draw gold coin
void drawGoldenDisk(GLUquadricObj* quadratic, float xCoord, float yCoord, float zCoord);

// draw the maze by segmentation, push and pop
void drawMaze(GLUquadricObj* quadratic, double blockStep);
// calculate x, y coordinate in maze
float toWorldX(float x);
float toWorldY(float y);
//update positions when they move
void updatePosition(float *x, float *y, int dirX, int dirY, float speed); 

#endif
