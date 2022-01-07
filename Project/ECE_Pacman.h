/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: DEC 1, 2020!!
Description: .h for Pacman. 
1-Pac-man can be drawn as a yellow sphere
2. Pac-main is controlled in the main thread using the
a. Left, right, up, down arrow keys to change pac-man’s direction
Texture of pacman is disabeled for final. 
*/
#ifndef PACMAN
#define PACMAN


class ECE_Pacman
{
private:
	// field of the class
	int row;
	int col;
	float xLoc;
	float yLoc;
	float xCoord;
	float yCoord;
	float zCoord;
	int dirX;
	int dirY;
	float radius;
	float speed;
	int pathMap[20][17] = {{0}};

public:
	// defined methods
	ECE_Pacman();

	// setting function for coordinates
	void setLoc(float x, float y);

	// set direction
	void setDir(int x, int y);

	// update the map of the shortest steps to each cell from pacman
	void updatePathMap();

	// getter for step count to the cell (row, col)
	int stepCount(int row, int col);

	// getters
	int getRow();
	int getCol();

	// move pacman
	void move();

	void draw(); // Draw pacman
	void drawTexture(unsigned int texture); //used in texture mapping in drawface
	void drawFace(); //aading face to pace man as a texture
};

#endif
