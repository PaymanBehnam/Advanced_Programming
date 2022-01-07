/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: OCT 30, 2020!!
Description: .h for drawing. 
ECE_Pacman class for drawing pac-man 1
1. Pac-man can be drawn as a yellow sphere
a. Pac-man is static and does not move.
*/
class ECE_Pacman
{
private:
    //field of the class.
    float xCoord;
    float yCoord;
    float zCoord;
    float radius;
public:
    //defined methods
    ECE_Pacman();
    //getter functions for coordinates
    float getXCoordinate();
    float getYCoordinate();
    float getZCoordinate();
    //setting function for coordinates
    void setCoordinate(float x, float y, float z);

    void draw(float x, float y, float z); // Draw pacman 
    void drawTexture(unsigned int texture); //used in texture mapping in drawface
    void drawFace(); //aading face to pace man as a texture
};


