/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: OCT 30, 2020!!
Description: .cpp for drawing. 
i. ECE_Ghost class for drawing the four ghosts
1. Ghost can be made with a sphere for a head and cylinder for body.
2. Each ghost needs to have a unique color
a. Red, green, orange, pink
3. The ghosts are static and do not move.
*/
#include <GL/glut.h> // on linux

typedef enum {RED, BLUE, PINK, YELLOW} color;

class ECE_Ghost {
private:     
    //field of the class.
    float xCoord;
    float yCoord;
    float zCoord;
    color ghostColor;

    float radius;
    float height; 
public:
    //defined methods
    ECE_Ghost(color ghostCol);
    //getter functions for coordinates
    float getXCoordinate();
    float getYCoordinate();
    float getZCoordinate();

    //setter function for coordinates

    void setCoordinate(float x, float y, float z);

    
    void draw(GLUquadricObj* quadratic, float x, float y, float z); // This function draws the ghost with the correct texture and the eyes facing the correct direction

    //draw eyes' ghost
    void drawEye();
    //used in texture mapping for draw eye
    void drawTexture(unsigned int texture);
};

