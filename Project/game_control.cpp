/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .cpp for game_control. different action to control the gameexcept using keyboard arrows!
*/
#include <iostream>
#include <string>
//#include <GL/glut.h>
#include <GLUT/glut.h> //on MAC
#include <math.h>
#include <stdio.h>
#include <string.h>
// //#include <GL/glew>
// #include <GL/glext.h>
// #include <GL/freeglut.h>
// #include <GL/freeglut_ext.h>

#include "game_control.h"
#include "maze.h"

//PFNGLWINDOWPOS2IPROC glWindowPos2i;
//glWindowPos2i =  (PFNGLWINDOWPOS2IPROC) glutGetProcAddress("glWindowPos2i");

// init variables for game state
GameControl::GameControl() {
	time = 0;
	started = false;
	ended = false;
	ghostReleaseInterval = 2000; //every 2 sec ghost realse from their location
	powerup = false;
	powerupTime = 0;
	pacmanLives = 3;

	remainedCoins = 0;
	gainedCoins = 0;
	remainedPowerups = 0;

	// count coin and powerups in maze variable
	for (int i = 0; i < rowNo; i++) {
		for (int j = 0; j < colNo; j++) {
			if (maze[i][j] == 1) {
				remainedCoins++;
			}

			if (maze[i][j] == 2) {
				remainedPowerups++;
			}
		}
	}
}

// start game
void GameControl::start() {
	started = true;
}

// update game process with time interval delta
void GameControl::update(int delta) {
	if (!started) {
		return;
	}

	// increase game time by delta
	time += delta;

	// check positions of ghosts and pacman and change game state
	for (int i = 0; i < 4; i++) {
		// ghosts leave their den with time interval
		if (time > i * ghostReleaseInterval) {
			ghosts[i].started = true;
		}

		// powerup is invalid 5 sec after pacman consumes it
		if (powerup && time - powerupTime > 5000) {
			powerup = false;
		}

		// when pacman consumes powerup, ghosts run away from him
		if (powerup) {
			ghosts[i].chase = false;
		} else {
			ghosts[i].chase = true;
		}

		// check if pacman meets ghosts or not
		if (pacman->getRow() == ghosts[i].getRow() && pacman->getCol() == ghosts[i].getCol()) {
			if (!powerup) {
				pacmanLives--;
				initPosition();
			} else {
				ghosts[i].dead = true;
				ghosts[i].started = false;
				ghostDeadTimes[i] = time;
				ghosts[i].setLoc(ghostInitPositions[i][0], ghostInitPositions[i][1]);
			}

		}

		// ghosts respawn 5 sec after they were dead
		if (ghosts[i].dead && ghostDeadTimes[i] + 5000 < time) {
			ghostDeadTimes[i] = 0;
			ghosts[i].dead = false;
			ghosts[i].started = true;
		}

		// pacman gets a powerup
		if (maze[pacman->getRow()][pacman->getCol()] == 2) {
			maze[pacman->getRow()][pacman->getCol()] = 4;
			powerupTime = time;
			powerup = true;
			remainedPowerups--;
		}

		// pacman gets a coin
		if (maze[pacman->getRow()][pacman->getCol()] == 1) {
			maze[pacman->getRow()][pacman->getCol()] = 4;
			remainedCoins--;
			gainedCoins++;
		}

		// if conditions are met, then game over
		if ((remainedPowerups <= 0 && remainedCoins <= 0) || pacmanLives == 0) {
			gameOver();
		}

	}

}

// setter for pacman
void GameControl::setPacman(ECE_Pacman *p) {
	pacman = p;
}

// setter for ghosts
void GameControl::setGhosts(ECE_Ghost *gs) {
	ghosts = gs;
}

// initialize positions of pacman and ghosts
void GameControl::initPosition() {
	time = 0;
	started = false;

	pacman->setLoc(8, 15);
	pacman->setDir(0, 0);

	for (int i = 0; i < rowNo; i++) {
		for (int j = 0; j < colNo; j++) {
			ghostMap[i][j] = 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		ghosts[i].setLoc(ghostInitPositions[i][0], ghostInitPositions[i][1]);
		ghostMap[ghostInitPositions[i][1]][ghostInitPositions[i][0]] = 1;
		ghosts[i].started = false;
	}
}
//print on cout when the game is ended.
void GameControl::gameOver() {
	ended = true;
	std::cout << "GAME OVER!" << std::endl;
}
//The following is for showing scores and lives: This works in mac versions due to glew library not available in the PACE-ICE and also glWindowPos2i(100, 450) function not supporsted in PACE-ICE;
void GameControl::drawText() {
	// glMatrixMode(GL_MODELVIEW);
	// glPushMatrix();
	// glLoadIdentity();

	// gluOrtho2D(0, 10, 0, 10);
	// glColor3f(1.0, 1.0, 1.0);

	// glPixelStorei sets pixel storage modes that affect the operation of subsequent glReadPixels as well as the unpacking of texture patterns
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	//specify the raster position in window coordinates for pixel operations
	glWindowPos2i(100, 450);
	
	// glRasterPos2i(100, 100);

	float posArray[4];
	glGetFloatv( GL_CURRENT_RASTER_POSITION, &posArray[0] );

	// std::cout << "raster pos: " << posArray[0] << posArray[1] << posArray[2] << posArray[3] << std::endl;

	std::string liveString = "Lives: ";
	//font for printing: GLUT_BITMAP_HELVETICA_18
	for (int i = 0; i < liveString.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, liveString[i]);
	}

	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, std::to_string(pacmanLives)[0]);

	std::string scoreString = "    Scores: ";

	for (unsigned int i = 0; i < scoreString.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreString[i]);
	}

	std::string scoreNumber = std::to_string(gainedCoins);

	for (unsigned int i = 0; i < scoreNumber.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, scoreNumber[i]);
	}

	// glPopMatrix();
}
