/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .h for game_control. different action to control the gameexcept using keyboard arrows!
*/
#ifndef GAME_CONTROL
#define GAME_CONTROL

#include "ECE_Ghost.h"
#include "ECE_Pacman.h"


class GameControl {

private:

	int time;  // game time in milisecond
	bool started;  // shows if game started or not
	int ghostReleaseInterval;  // ghosts are released every 2 seconds from their den
	ECE_Pacman *pacman; //make object of pacman to be able to control it.
	ECE_Ghost *ghosts; ////make object of ghost to be able to control it.
	bool powerup;  // pacman consumed powerup and it's still valid
	int powerupTime;  // when pacman consumed powerup
	int pacmanLives; //keep # lives of pacman (3 max)
	int remainedCoins; // keep remained coins
	int gainedCoins; // how mch we gained for the coins
	int remainedPowerups; ////keep the eaten powerups
	int ghostDeadTimes[4] = {0};  // when ghosts were dead
	int ghostInitPositions[4][2] = {  // initial position of ghosts in den
		{8, 8}, {8, 9}, {9, 9}, {7, 9}
	};

public:

	bool ended; //to see if the game is ended or no/

	GameControl();
	void update(int delta);  // update game process with interval in milisecond!check the status of game including if to finish game or not! Checking if pacman consumes powerup and coins
	void start();
	void setPacman(ECE_Pacman *p);  // setter for pacman
	void setGhosts(ECE_Ghost *gs);  // setter for ghosts
	void initPosition();  // initialize positions of pacman and ghosts
	void gameOver();  // called when game over
	void drawText();  // draw scores and lives of pacman

};

#endif
