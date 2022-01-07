
/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: Sep 13, 2020!!
Description: .cpp file. 
*/

//#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <climits>
#include "MyGrid.h"


using namespace std;

//check if what we read is number
/*
bool isNumber(string str){
    for (unsigned long int  j = 0; j < str.length(); j++)
        if (isdigit(str[j]) == false)
            return false;
    return true;
}
*/
///getter reutrns long and setter returns void. 

long MyGrid::getMyX() const{
    //getter X
    return myX;
}
void MyGrid::setMyX(long x){
    //setter X
    myX = x;
}
long MyGrid::getMyY() const{
    //getter Y
    return myY;
}
void MyGrid::setMyY(long y){
    //setter y
    myY = y;
}
/*vector< vector<long> > MyGrid::getGridElements() const{
      return gridElements;
}*/

long MyGrid::getNumRows() const{
    //return 1s dimention of a 2d vector
    return gridElements.size();
}
long MyGrid::getNumCols() const{
    // return 2nd dimention of a 2d vector
	if(gridElements.size() == 0){
		return 0;
	}
    return gridElements[0].size();
}
void MyGrid::zeroOutGrid(){
    //Different ways to zero all elemets of a gird. Since the grid is first created, we  can use assignment like matrix to make all elements zero.
    //gridElements(getNumRows(), vector<long> (getNumCols(), 0));
    //gridElements.resize(getNumRows(), std::vector<long>( getNumCols(), 0));
    for (long i = 0; i < getNumRows(); i++) { 
        for (long j = 0; j < getNumCols(); j++) { 
            gridElements[i][j] = 0; 
        } 
    } 
}
MyGrid::MyGrid(long x, long y, long length, long width){
    //Constructor: inputs are corrdination and dimention of the class. we make all values zero here. Return a MyGrid object.
    setMyX(x);
    setMyY(y);
    if (length > 0 && width > 0 && x >= 0 && y >= 0){
        gridElements.resize(length);
        for (long i = 0; i < length; i++)
            gridElements[i].resize(width);
        zeroOutGrid();
    }
}
//default constructors 
MyGrid::MyGrid(){}

bool MyGrid::loadGridFromFile(const string filename) {
    //read elements from  an input file, returns true if the reading is successful and false otherwise.
    string line;
    long static numRows, numCols;
    string term ;
    ifstream infile;
    
    infile.open(filename, std::ifstream::in);
	if (! infile) {
    	cout << "Error, file couldn't be opened" << endl; 
    	exit(1); 
	} 

    /*another way of reading a line and check validity
      string token;
      getline(infile, line);
      istringstream iss0(line);
      getline(iss0, token, ' ');
      if (!isNumber(token.c_str())  ||  stoull(token.c_str()) > ULONG_MAX || stoul(token.c_str()) <= 0) {return false;}
    */ 

    infile >> myX;
    infile >> myY;
    infile >> numRows;
    infile >> numCols;

    //Check validity
    if (numRows <=0 || numCols <=0 || myX < 0 || myY < 0) return false; 
   
    for (long i = 0; i < numRows; i++){
        //initialize gridElements by push_back. Put a row in 2d vector 
        vector<long> temp;
        for (long j=0;  j <  numCols; j++){
            //Intiliza every row
		    long term;
            infile >> term;
            temp.push_back(term);
        }
        gridElements.push_back(temp);
	
    }

    return true;
}
void MyGrid::addGrid(MyGrid const& secGrid) {
    // A helper method for adding two grids (secGrid is added to current Grid). Return is void.
	for(int i = 0; i < secGrid.getNumRows(); i++){
		for(int j = 0; j < secGrid.getNumCols(); j++){
            //add elements of the new one to exisitng one. All is needed to set the corresponding indices.
            gridElements[this->getMyY() - secGrid.getMyY()+i][secGrid.getMyX() - this->getMyX()+j] += secGrid.gridElements[i][j];
                   
        }
	}
}

void MyGrid::subGrid(MyGrid const& secGrid) {
    //// A helper method for subtracting two grids (secGrid is added to current Grid). Return is void.
	for(int i = 0; i < secGrid.getNumRows(); i++){
		for(int j = 0; j < secGrid.getNumCols(); j++){
            //add elements of the new one to exisitng one. All is needed to set the corresponding indices.
            gridElements[this->getMyY() - secGrid.getMyY()+i][secGrid.getMyX() - this->getMyX()+j] -= secGrid.gridElements[i][j];

        }
	}
}

MyGrid MyGrid::operator+(MyGrid const& secGrid) const{
    //Forming new grid by + operation. A MyGrid object is returned.

    //these operators use the extents of the grid and the upper left-hand corner to create a new grid that has the maximum extents of the two grids.
	//the X of new Grid is the minimum X of the two Grids
    long newX = min(this->getMyX(), secGrid.getMyX());
    //the Y of new Grid is the maximux X of the two Grids
	long newY = max(this->getMyY(), secGrid.getMyY());
    //computing length and width of newly formed grid
	long length = newY - min(this->getMyY()-this->getNumRows(), secGrid.getMyY() - secGrid.getNumRows());
	long width = max(this->getMyX()+this->getNumCols(), secGrid.getMyX() + secGrid.getNumCols()) - newX;

    //Constructing new object
    MyGrid newGrid(newX, newY, length, width);
    //adding two grids to the new formed one. We construct an object, then add secGrid and then adding existing one.
    newGrid.addGrid(secGrid);
    newGrid.addGrid(*this);

    return newGrid;
}

MyGrid MyGrid::operator-(MyGrid const& secGrid) const{
    //Forming new grid by - operation. All is the same as above except we need to use subGrid. Pay attention for adding exisiting one we must use addGrid.
    //A MyGrid object is returned.
    long newX = min(this->getMyX(), secGrid.getMyX());
	long newY = max(this->getMyY(), secGrid.getMyY());
	long length = newY - min(this->getMyY()-this->getNumRows(), secGrid.getMyY() - secGrid.getNumRows());
	long width = max(this->getMyX()+this->getNumCols(), secGrid.getMyX() + secGrid.getNumCols()) - newX;

    MyGrid newGrid(newX, newY, length, width);
	newGrid.subGrid(secGrid);
	newGrid.addGrid(*this);
    
    return newGrid;

}

MyGrid MyGrid::operator+(long const& value) const{
    //Adds a long to all the elements in the MyGrid object. A MyGrid object is returned.
    //MyGrid* ptr =  const_cast <MyGrid *> (this); :another way of access and change const values.
    MyGrid AddGrid(this->getMyX(), this->getMyY(), this->getNumRows(), this->getNumCols() ); //    //Constructing new object with the values of exisiting object. 

    for (long i = 0; i < this->getNumRows(); i++) 
        // nest loop for access to all elements. first looop on Rows and then Columns. 
        for (long j = 0; j < this->getNumCols() ; j++)
            //ptr->gridElements[i][j] = gridElements[i][j] + value; //another way
            AddGrid.gridElements[i][j] = gridElements[i][j] + value; //addition
    return AddGrid;
    //return *this;
}
MyGrid operator+(long const& lhs, MyGrid const& rhs){
    //he long value is added to all the elements in the MyGrid object. 
    //MyGrid* ptr =  const_cast <MyGrid *> (this);
    //becuase lhs is not an MyGrid bject, we need to implemet it as regular function. We cannot call a method on a non-object.
    MyGrid AddGrid(rhs.getMyX(), rhs.getMyY(), rhs.getNumRows(), rhs.getNumCols() ); // make an object and initiliza it. 
    for (long i = 0; i < rhs.getNumRows(); i++)
            // nested loop for access to all elements. first loop on Rows and then Columns. 
        for (long j = 0; j < rhs.getNumCols() ; j++)
            AddGrid.gridElements[i][j] = lhs+rhs.gridElements[i][j]; //addition
    return AddGrid;
}

void MyGrid::deepCopy(MyGrid secGrid){
    //deepCopy : Copying an object to another one. We can use a copy constructor. return void.
	this->myX = secGrid.myX;
    this->myY = secGrid.myY;
    for(long i = 0; i < secGrid.getNumRows(); i++){
        // nested loop for access to all elements. first loop on Rows and then Columns. 
        // put a row in a 2d vector.
		vector<long> temp;
		for(long j = 0; j < secGrid.getNumCols(); j++){
            //process entire row
			temp.push_back(secGrid.gridElements[i][j]);
		}
		gridElements.push_back(temp);
	}
}


MyGrid& MyGrid::operator+=(MyGrid const& secGrid){
    //add one gird to another one with the same size and equall elements.Return a MyGrid Object.
	if(this->getNumRows() == 0 || this->getNumCols() == 0){ //make sure the object is not null and copy an object proper;y.
		deepCopy(secGrid);
	} else {
    for (long i = 0; i < this->getNumRows(); i++){
        //// nested loop for access to all elements. first looop on Rows and then Columns. 
        for (long j = 0; j < this->getNumCols() ; j++){
            gridElements[i][j] = gridElements[i][j] + secGrid.gridElements[i][j];
        }
    }
    }
    return *this;
}


MyGrid& MyGrid::operator++(){ // Prefix
    //all the element values are increased by one. Return a MyGrid Object.
    for (long i = 0; i < this->getNumRows(); i++) 
    //computing the value of each elements.  nested loop for access to all elements. first looop on Rows and then Columns. 
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j]+1;
    return *this;

}
MyGrid MyGrid::operator++(int){ // Postfix
    //all the element values are increased by one. Return a MyGrid Object.
    MyGrid temp = *this;  //we need to make a copy first and store exitsting one in temp; Then we should increment elements and then return the temp one. 
	//deepCopy(temp);
    for (long i = 0; i < this->getNumRows(); i++) 
    //computing the value of each elements
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j]+1;
    return temp;
}

MyGrid& MyGrid::operator--(){ // Prefix
    //all the element values are decreased by one. Return a MyGrid Object.
    for (long i = 0; i < this->getNumRows(); i++) 
    //computing the value of each elements
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j]-1 ;
    return *this;


}
MyGrid MyGrid::operator--(int){ // Postfix
    //  all the element values are decreased by one.  Return a MyGrid Object.
    MyGrid temp = *this;  ////we need to make a copy first and store exitsting one in temp; Then we should increment elements and then return the temp one. 
    //deepCopy(temp);
    for (long i = 0; i < this->getNumRows(); i++)
    //computing the value of each elements
        for (long j = 0; j < this->getNumCols() ; j++)
            gridElements[i][j] = gridElements[i][j] -1;
    return temp;
}

MyGrid MyGrid::operator-() const{
    //has the same effect as multiplying all the elements by -1. Return a MyGrid Object.
    MyGrid MulNegGrid(this->getMyX(), this->getMyY(), this->getNumRows(), this->getNumCols()); //creare a new object
    for (long i = 0; i < this->getNumRows(); i++) 
    //computing the value of each elements
        for (long j = 0; j < this->getNumCols(); j++){
            MulNegGrid.gridElements[i][j] = -1 * gridElements[i][j];
        }
    return MulNegGrid;
}

bool MyGrid::operator==(MyGrid const& secGrid) const{
    //the size and all the elements must be the same, and the upper left-hand offset must be the same. Retrun true if all things are fine and false otherwise.
    if (getNumRows() == secGrid.getNumRows() &&  getNumCols() == secGrid.getNumCols() && this->myX == secGrid.myX &&  this->myY == secGrid.myY){
        for (long i = 0; i < this->getNumRows(); i++)
        //check all the elements.
            for (long j = 0; j < this->getNumCols() ; j++)
                if (gridElements[i][j] != secGrid.gridElements[i][j])
                    return false;
        return true;
    }
    else{
        return false;
    }
}

fstream& operator<<(fstream& os, const MyGrid& gridIn){
    //this operator outputs the class using the same format as is used in reading in a MyGrid object. inputs are MyGridobject and output is fstream ( write in file)
    os << gridIn.getMyX();
    os << ' '; //add space between numbers
    os << gridIn.getMyY();
    os << '\n'; //add new line
    os << gridIn.getNumRows();
    os << ' ';
    os << gridIn.getNumCols();
    os << '\n';
    for (long i = 0; i < gridIn.getNumRows(); i++){ //add elements to the file
        for (long j = 0; j < gridIn.getNumCols() ; j++){
            os << gridIn.gridElements[i][j];
            if (j != gridIn.getNumCols()-1) //to avoid any space at the end of line
                os << ' ';
        }
        os << '\n';
    }
    return os;
}






