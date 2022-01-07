

/*Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: OCT 30, 2020!!
This is the implemetation of the maze , coin, golden coins.
Drawing maze is just hard coding 
*Push matrix
*Find appropriate location and rotation for segment cylinder (glTranslatef & glRotatef)
*draw segment cylinder 
*Pop matrix
Since the pronlem didnt asked for the specific class for them, I just defined there here and not put in main to avoid make the main ugly!
some of the library functions are used in other files. So, I may not  put comment here if I alreay did in some other files to avoid over commenting!
source of the used functions: https://docs.microsoft.com/en-us/windows/win32/opengl/gl-functions

*/
#include <GL/glut.h>
int rowNo=20; //define number of rows
int colNo=17; ////define number of columns
/**
 *      0: Wall, Ghost, Pacman, Empty
 *      1: Coin
 *      2: Power up golden flat disc
 */
// 2D array defines the size of the maze and also what each tile contains
int maze[20][17] =
        {       {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
                {2,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,2},
                {1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1},
                {1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
		{1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
		{1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1},
		{2,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,2},
		{0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0},
		{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
		{1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////// draw silver coin//////////////////////////////////////////////////////////////
void drawCoin(float xCoord, float yCoord, float zCoord){
   glPushMatrix();
        glColor3ub(192, 192, 192); //silver color
        glTranslatef(xCoord,yCoord,zCoord);
        glutSolidSphere(0.02,32,32); //draw sphere
    glPopMatrix();

}
///////////////////// draw gold coin///////////////////////////////////////////////////////////////
/*void drawGoldenDisk(GLUquadricObj* quadratic, float xCoord, float yCoord, float zCoord){
   glPushMatrix();
        glColor3ub(212, 175, 55); ////specify the gold color. GLubyte red,GLubyte green,GLubyte blue)
        glTranslatef(xCoord,yCoord,zCoord);
        gluDisk(quadratic, 0, 0.04f, 1024, 1024); //draw disck
    glPopMatrix();
}*/
//different way of draw gold coin
void drawGoldenDisk(GLUquadricObj* quadratic, float xCoord, float yCoord, float zCoord){
  glPushMatrix();
        glColor3ub(212, 175, 55); /////specify the gold color. GLubyte red,GLubyte green,GLubyte blue)
        //glTranslatef(xCoord,yCoord,zCoord);
        glPushMatrix();
            glTranslatef(xCoord,yCoord,zCoord);
            // Place a cylinder as the base of the coin
            gluCylinder(quadratic, 0.04, 0.04, 0.02, 16, 16);
        glPopMatrix();
        glPushMatrix();
            // Place a circular disk on top the base cylinder
            glTranslatef(xCoord,yCoord,zCoord+0.02);
            gluDisk(quadratic, 0, 0.04f, 32, 32); //draw disk
        glPopMatrix();
    glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////draw the maze by segmentation, push and pup//////////////////////////////////////////////////
void drawMaze(GLUquadricObj* quadratic, double blockStep){
        GLfloat radius = 0.02f;  // thin cylinder
	// Create side walls/////////////////////////////////////////////////////
	glPushMatrix();
	    glTranslatef(0, 0, 0); //shifting. origin: no shift
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); //rotating
            gluCylinder(quadratic, radius, radius, blockStep*18, 32, 32); //draw wall (cylinder)
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(0, 0, 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*7, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(0, blockStep*(-7), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*3, blockStep*(-7), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(0, blockStep*(-9), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(0, blockStep*(-11), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*3, blockStep*(-11), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(0, blockStep*(-13), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(0, blockStep*(-13), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*8, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(0, blockStep*(-21), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*18, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*18, blockStep*(-13), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*8, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-13), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-11), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-11), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-9), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-7), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-7), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*18, 0, 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*7, 32, 32);
	glPopMatrix();
	// End side walls/////////////////////////////////////////////////////
	//Upper-left small square with size of 1*1 /////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*2, blockStep*(-2), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*2, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*2, blockStep*(-3), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*3, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//Upper-left medium rectangle with size of 1*2 /////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-2), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-3), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*7, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//Upper-right medium rectangle with size of 1*2 /////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*11, blockStep*(-2), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*11, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*11, blockStep*(-3), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*13, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//Upper-right small square with size of 1*1 /////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-2), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-3), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*16, blockStep*(-2), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//central big rectangle with size of 2*4 /////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*7, blockStep*(-9), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*7, blockStep*(-9), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*7, blockStep*(-11), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*11, blockStep*(-9), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// vertical line that seperates upper left and upper right sections //////
	glPushMatrix();
	    glTranslatef(blockStep*9, 0, 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*3, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Horizontal and vertical lines that seperate upper left and upper right sections //////
	glPushMatrix();
	    glTranslatef(blockStep*7, blockStep*(-5), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*9, blockStep*(-5), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Small horizontal lines in both left and right sides in the upper section
	glPushMatrix();
	    glTranslatef(blockStep*2, blockStep*(-5), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-5), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Vertical & horizontal lines in both upper left and upper right sides of central rectangle
	// Upper-Left of central rectangle //////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-5), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-7), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	// Upper-Right of central rectangle //////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*13, blockStep*(-5), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*11, blockStep*(-7), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Small vertical lines in both lower-left and lower-right sides of central rectangle
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-11), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*13, blockStep*(-11), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Two Horizontal-vertical-lines in the below section of central rectangle (The initial position of Pacman)
	//Upper //////////////////////////////////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*7, blockStep*(-13), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*9, blockStep*(-13), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//Lower //////////////////////////////////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*7, blockStep*(-17), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*4, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*9, blockStep*(-17), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Small horizontal lines in both left and right sides of initial positoin of Pacman
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-15), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*11, blockStep*(-15), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	// Small horizontal lines in both lower-left and lower-right sides of maze
	glPushMatrix();
	    glTranslatef(0, blockStep*(-17), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*17, blockStep*(-17), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Two Horizontal-vertical-lines in both left and right sides of initial position of Pacman
	//Left //////////////////////////////////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*2, blockStep*(-15), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*3, blockStep*(-15), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//Right //////////////////////////////////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-15), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*1, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*15, blockStep*(-15), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// Two Big-vertical-Small-Horizontal-lines in both lower-left and lower-right sides of the maze
	//Left /////////////////////////////////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*5, blockStep*(-17), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*2, blockStep*(-19), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*5, 32, 32);
	glPopMatrix();
	//Right //////////////////////////////////////////////////////////////////
	glPushMatrix();
	    glTranslatef(blockStep*13, blockStep*(-17), 0);
	    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*2, 32, 32);
	glPopMatrix();
	glPushMatrix();
	    glTranslatef(blockStep*11, blockStep*(-19), 0);
	    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic, radius, radius, blockStep*5, 32, 32);
	glPopMatrix();
	//////////////////////////////////////////////////////////////////////////
}

/* The other way of drawing cylinder. however I didnt use it finally. 
void draw_cylinder(GLfloat radius, GLfloat height)
{
    glPushMatrix(); //

    radius = 0.02f;  // thin cylinder

    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1; 
    // Draw the tube 
    //glColor3ub(R-40,G-40,B-40);
    glColor3f(0.0,0.0,1.0); // set the color to blue!
    //glBegin and glEnd delimit the vertices that define a primitive or a group of like primitives. glBegin accepts a single argument that specifies in which of ten ways the vertices are interpreted. 
	//Draws a connected group of quadrilaterals. One quadrilateral is defined for each pair of vertices presented after the first pair. Vertices 2 ⁢ n - 1 , 2 ⁢ n , 2 ⁢ n + 2 , and 2 ⁢ n + 1 define quadrilateral n. N 2 - 1 quadrilaterals are drawn. Note that the order in which vertices are used to construct a quadrilateral from strip data is different from that used with independent data.
	glBegin(GL_QUAD_STRIP); 
    angle = 0.0;
    while( angle < 2*PI ) { //traverese the pyramic 
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height); //Specifies a vertex.
        glVertex3f(x, y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();
    // Draw the circle on top of cylinder 
    //glColor3ub(R,G,B);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON); //Draws a single, convex polygon. Vertices 1 through N define this polygon.

    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();

   // Pop matrix to ignore above transformations on future objects
    glPopMatrix();

}
*/