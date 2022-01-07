/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: OCT 30, 2020!!
Description: .cpp for drawing. 
i. ECE_Ghost class for drawing the four ghosts
1. Ghost can be made with a sphere for a head and cylinder for body.
2. Each ghost needs to have a unique color
a. Red, green, orange, pink
3. The ghosts are static and do not move.
some of the library functions are used in other files. So, I may not  put comment here if I alreay did in some other files to avoid over commenting!

*/
#include "ECE_Ghost.h"
#include <GL/glut.h> // on linux


extern unsigned int ghost_eye_tex;
//Constructor
ECE_Ghost::ECE_Ghost(color ghostCol) {
    ghostColor = ghostCol;
	radius=0.06;
	height=0.08;
}

//getter functions for coordinattes,
float ECE_Ghost::getXCoordinate(){
    return xCoord;
}
float ECE_Ghost::getYCoordinate(){
    return yCoord;
}
float ECE_Ghost::getZCoordinate(){
    return zCoord;
}
//setter function for coordinattes,
void ECE_Ghost::setCoordinate(float x, float y, float z){
    xCoord = x;
    yCoord = y;
    zCoord = z;
}

// This function draws the ghost with the correct texture and the eyes facing the correct direction
void ECE_Ghost::draw(GLUquadricObj* quadratic, float x, float y, float z){
    setCoordinate(x,y,z);
    //The glPushMatrix and glPopMatrix functions push and pop the current matrix stack. it used to specify where we are. 
    glPushMatrix();
	 switch (ghostColor) {
            case RED:
            	glColor3f(1.0, 0.0, 0.0);
                break;
            case PINK:
            	glColor3f(1.0, 0.9, 0.9);		
                break;
            case BLUE:
            	glColor3f(0.0, 0.8, 0.8);		
                break;
            case YELLOW:
            	glColor3f(1.0, 0.82, 0.09);		
                break;
        }
    ////we end up being in a specific cordinate 
    glPopMatrix();
    glPushMatrix(); 
        ///These functions multiply the current matrix by a translation matrix to move an object
        glTranslatef(xCoord,yCoord,zCoord+height);
        //draw sphere
        glutSolidSphere((GLfloat)radius,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(xCoord, yCoord, zCoord);
        //draw cylinder
        gluCylinder(quadratic, (GLfloat)radius, (GLfloat)radius, (GLfloat)height, 32, 32);
    glPopMatrix();
    glPushMatrix();
        drawEye();
    glPopMatrix();
}

//Draws the texture passed in given the height, length 
void ECE_Ghost::drawTexture(unsigned int texture)
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);   // Set background colour to white. This should never be seen but allows a visual debug to see if a texture hasn't
                                    // been loaded or bound correctly.
    float widthCentre = radius;
    float verticalCentre = radius;
    // Translate to center of object to rotate about its origin 
    glTranslatef(xCoord,yCoord,zCoord+height);
    //glRotatef(20, 1.0f, 0.0f, 0.0f); // Rotate
    // Enable texturing and bind the specific object
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Specify texture coordinates
    //glBegin and glEnd delimit the vertices that define a primitive or a group of like primitives. glBegin accepts a single argument that specifies in which of ten ways the vertices are interpreted. 
	//Draws a connected group of quadrilaterals. One quadrilateral is defined for each pair of vertices presented after the first pair. Vertices 2 ⁢ n - 1 , 2 ⁢ n , 2 ⁢ n + 2 , and 2 ⁢ n + 1 define quadrilateral n. N 2 - 1 quadrilaterals are drawn. Note that the order in which vertices are used to construct a quadrilateral from strip data is different from that used with independent data.
    glBegin(GL_QUADS);
        glTexCoord2f (0.0f, 0.0f);      // Lower left corner
        glVertex2f(-widthCentre, -verticalCentre);
        glTexCoord2f (1.0f, 0.0f);      // Lower right corner
        glVertex2f(widthCentre, -verticalCentre);
        glTexCoord2f (1.0f, 1.0f);      // Upper right corner
        glVertex2f(widthCentre, verticalCentre);
        glTexCoord2f (0.0f, 1.0f);      // Upper left corner
        glVertex2f(-widthCentre, verticalCentre);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    // Pop matrix to ignore above transformations on future objects
    glPopMatrix();
}

//add eye texture to ghost
void ECE_Ghost::drawEye(){
    glPushMatrix();
        //unsigned int ghost_eye_tex;
        glEnable(GL_BLEND);
        //Transparency is best implemented using blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest. Note that this transparency calculation does not require the presence of alpha bitplanes in the frame buffer.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        drawTexture(ghost_eye_tex);
    glPopMatrix();
}

