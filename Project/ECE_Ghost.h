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
Texture is disabled for the ghosts 
*/
#pragma once
#ifndef GHOST
#define GHOST

//#include <GL/glut.h>  // on linux
#include <GLUT/glut.h> //on MAC

#include "ECE_Pacman.h"

//color of ghost
typedef enum { RED, GREEN, PINK, ORANGE } color;

class ECE_Ghost {
private:
	// field of the class
	int row;  // row in maze
	int col;  // column in maze
	float xLoc;  // x coordinates in maze
	float yLoc;  // y coordinates in maze
	float xCoord;  // x coordinates in world space for rendering
	float yCoord;  // y coordinates in world space for rendering
	float zCoord;  // z coordinates in world space for rendering
	int dirX;  // x direction of movement
	int dirY;  // y direction of movement
	float speed; //speed of the ghost
	color ghostColor; //color of the ghost

	ECE_Pacman *pacman; ////make an object for pacman here so they can chase pacman.

	//parameter of the shape of the ghost
	float radius;
	float height;

public: //bool values for chaseing, being started and dead of ghosts.
	bool started;
	bool chase;
	bool dead;

	// defined methods
	ECE_Ghost(color ghostCol);

	// setters
	void setPacman(ECE_Pacman *p);

	void setLoc(float x, float y);

	// getters
	int getRow();
	int getCol();

	// move ghost
	void move();

	void draw(GLUquadricObj* quadratic);

	void draw(GLUquadricObj* quadratic, float x, float y, float z); // This function draws the ghost with the correct texture and the eyes facing the correct direction

	// draw eyes' ghost
	 //void drawEye();
	// used in texture mapping for draw eye
	 void drawTexture(unsigned int texture);
};

#endif
