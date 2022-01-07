
/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: OCT 30, 2020!!
Description: .cpp for drawing. 
ECE_Pacman class for drawing pac-man 1
1. Pac-man can be drawn as a yellow sphere
a. Pac-man is static and does not move.
some of the library functions are used in other files. So, I may not  put comment here if I alreay did in some other files to avoid over commenting!
*/
#include <GL/glut.h> // on linux
#include "ECE_Pacman.h"
extern unsigned int pac_tex;

//constuctor
ECE_Pacman::ECE_Pacman()
{
    radius = 0.06;
}
//getter functions
float ECE_Pacman::getXCoordinate(){
    return xCoord;
}
float ECE_Pacman::getYCoordinate(){
    return yCoord;
}
float ECE_Pacman::getZCoordinate(){
    return zCoord;
}
//setter functions
void ECE_Pacman::setCoordinate(float x, float y, float z){
    xCoord = x;
    yCoord = y;
    zCoord = z;
}

//Draw pacman 
////////////////////////////////////////////////////////////////////
void ECE_Pacman::draw(float x, float y, float z){
   setCoordinate(x,y,z);
   glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
            glTranslatef(xCoord,yCoord,zCoord);
            glutSolidSphere(radius,10,10);
    glPopMatrix();
    glPushMatrix();
        drawFace();
    glPopMatrix();
 
}

////////////////////////////////////////////////////////////////////////////////////
//Draws the texture passed in given the height, length 
void ECE_Pacman::drawTexture(unsigned int texture)
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);   // Set background colour to white. This should never be seen but allows a visual debug to see if a texture hasn't
                                    // been loaded or bound correctly.
    float widthCentre = radius;
    float verticalCentre = radius;
    // Translate to center of object to rotate about its origin 
    glTranslatef(xCoord,yCoord,zCoord);
    //glRotatef(20, 1.0f, 0.0f, 0.0f); // Rotate
    // Enable texturing and bind the specific object
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    // Specify texture coordinates
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

//texture mappping for adding face to Mr. Packman
void ECE_Pacman:: drawFace()
{
    glPushMatrix();
        glEnable(GL_BLEND);
        //Transparency is best implemented using blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest. Note that this transparency calculation does not require the presence of alpha bitplanes in the frame buffer.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         drawTexture(pac_tex);
    glPopMatrix();
}

