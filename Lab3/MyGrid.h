
/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: Sep 13, 2020!!
Description: .h file. I added several methods. Detailed comments are in cpp file. 
Complete a class called MyGrid that has a member variable gridElements that is a dynamic two-dimensional array of elements (type long) of m rows by n columns.
 The class also contains two long variables called myX and myY which indicates the upper left-hand location of element of the grid. It has severa methods implemented 
 in .cpp
*/

#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;


class MyGrid{

public:
    long getNumRows() const;
    long getNumCols() const;

    //Getter and setter methods of the class for X and Y, added by Payman.
    long getMyX() const;
    void setMyX(long x);
    long getMyY() const;
    void setMyY(long y);
    //vector< vector<long> > getGridElements() const;

    
    //Define constructors of the class added by Payman
    MyGrid(long x, long y, long length, long width);
    MyGrid();

    bool loadGridFromFile(const string filename);

    void zeroOutGrid();

    MyGrid operator+(MyGrid const&) const;
    MyGrid operator-(MyGrid const&) const;

    MyGrid operator+(long const&) const;

    friend MyGrid operator+(long const& lhs, MyGrid const& rhs);

    // Addition assignment
    MyGrid& operator+=(MyGrid const&);
    // Increment
    MyGrid& operator++(); // Prefix
    MyGrid operator++(int); // Postfix

    MyGrid& operator--(); // Prefix
    MyGrid operator--(int); // Postfix

    MyGrid operator-() const;

    bool operator==(MyGrid const&) const;

    friend fstream& operator<<(fstream& os, const MyGrid& gridIn);
    
    ////deepCopy : Copying an object to another one. We can use a copy constructor, added by Payman.
    void deepCopy(MyGrid secGrid);
    //use as a helper method for adding two grids, added by Payman.
    void addGrid(MyGrid const& secGrid);
    //use as a helper method for subtracting two grids, added by Payman.
    void subGrid(MyGrid const& secGrid);

private:
    long myX, myY;
    vector< vector<long> > gridElements;
};



