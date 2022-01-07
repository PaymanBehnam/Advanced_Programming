#ifndef PACMAN
#define PACMAN


class ECE_Pacman
{
private:
	// field of the class
	int row;
	int col;
	float xLoc; //the x coordinate in the maze
	float yLoc; //the y coordinate in the maze
	//Objects are rendered in 3d space (x,y,z). It is called world space.
	float xCoord; //the x coordinate in world space for rendering
	float yCoord; // the y coordinate in world space for rendering
	float zCoord;// the z coordinate in world space for rendering
	int dirX; // the x direction of movement in maze
	int dirY; //the y direction of movement in maze
	float radius; //radious of the pacman
	float speed; //speed of the pacman.
	int pathMap[20][17] = {{0}}; // the whole path that pacman will pass

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
	//void drawFace(); //aading face to pace man as a texture
};

#endif
