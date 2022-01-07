/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: Oct 13, 2020!!
Description: 
This program solves the the stream of Sudoku puzzles concurrently.  
The main function needs to dynamically determine the maximum number of threads that can run concurrently. 
The main() function should then spawn (numThreads-1) threads calling the function solveSudokuPuzzles().
I use online solutions for solving the individual Sudoku problem: https://www.geeksforgeeks.org/sudoku-backtracking-7/
MaxOS compile: clang++ -Xpreprocessor -fopenmp -I/usr/local/include -L/usr/local/lib -lomp  main.cpp 
Linux compile: g++ -std=c++11 main.cpp -lpthread
*/
#include "Lab3_Problem1.h" 
#include <fstream> 
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <climits>
#include <stdlib.h>     
#include <random>
#include <omp.h>
//#include "/usr/local/opt/libomp/include/omp.h" //for run in mac
#include <chrono>
#include <thread>
#include <mutex>

//using namespace std::chrono; //for time measuring

using namespace std; 
  





// This function finds an entry in grid 
// that is still unassigned 
bool FindUnassignedLocation(int grid[N][N], int& row, int& col); 

// Checks whether it will be legal 
// to assign num to the given row, col 
bool isSafe(int grid[N][N], int row, int col, int num); 

/* Takes a partially filled-in grid and attempts 
to assign values to all unassigned locations in 
such a way to meet the requirements for 
Sudoku solution (non-duplication across rows, 
columns, and boxes) */
bool SolveSudoku(int grid[N][N]) { 
	int row, col; 

	// If there is no unassigned location, 
	// we are done 
	if (!FindUnassignedLocation(grid, row, col)) 
		// success! 
		return true; 

	// Consider digits 1 to 9 
	for (int num = 1; num <= 9; num++) { 
		// if looks promising 
		if (isSafe(grid, row, col, num)) { 
			// make tentative assignment 
			grid[row][col] = num; 

			// return, if success, yay! 
			if (SolveSudoku(grid)) 
				return true; 

			// failure, unmake & try again 
			grid[row][col] = UNASSIGNED; 
		} 
	} 
	// this triggers backtracking 
	return false; 
} 

/* Searches the grid to find an entry that is 
still unassigned. If found, the reference 
parameters row, col will be set the location 
that is unassigned, and true is returned. 
If no unassigned entries remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N], int& row, int& col) { 
	for (row = 0; row < N; row++) 
		for (col = 0; col < N; col++) 
			if (grid[row][col] == UNASSIGNED) 
				return true; 
	return false; 
} 

/* Returns a boolean which indicates whether 
an assigned entry in the specified row matches 
the given number. */
bool UsedInRow(int grid[N][N], int row, int num){
	for (int col = 0; col < N; col++) 
		if (grid[row][col] == num) 
			return true; 
	return false; 
} 

/* Returns a boolean which indicates whether 
an assigned entry in the specified column 
matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num) { 
	for (int row = 0; row < N; row++) 
		if (grid[row][col] == num) 
			return true; 
	return false; 
} 

/* Returns a boolean which indicates whether 
an assigned entry within the specified 3x3 box 
matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) { 
	for (int row = 0; row < 3; row++) 
		for (int col = 0; col < 3; col++) 
			if (grid[row + boxStartRow][col + boxStartCol] == num) 
				return true; 
	return false; 
} 

/* Returns a boolean which indicates whether 
it will be legal to assign num to the given 
row, col location. */
bool isSafe(int grid[N][N], int row, int col, int num) { 
	/* Check if 'num' is not already placed in 
	current row, current column and current 3x3 box */
	return !UsedInRow(grid, row, num) 
		&& !UsedInCol(grid, col, num) 
		&& !UsedInBox(grid, row - row % 3, 
						col - col % 3, num) 
		&& grid[row][col] == UNASSIGNED; 
} 

/* A utility function to print grid */
void printGrid(int grid[N][N]) { 
	for (int row = 0; row < N; row++) { 
		for (int col = 0; col < N; col++) 
			cout << grid[row][col] << " "; 
		cout << endl; 
	} 
} 



SudokuGrid::SudokuGrid(){ //deafult constructor
    m_strGridName = "Grid01";
   for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            gridElement[i][j] = '0';
        }
    }

}
fstream& operator<<(fstream& os,  SudokuGrid& gridIn){
    //this operator write the class using the same format as is used in reading in a SudokuGrid object. inputs are SudokuGrid and output is fstream ( write into a file)
    os <<"Grid ";
    os << gridIn.m_strGridName<<endl; //write the number
    for (int i = 0; i < N; i++){ //add elements to the file
        for (int j = 0; j < N ; j++){
            os << gridIn.gridElement[i][j];
        }
        os << '\n';
    }
    return os;
}

fstream& operator>>(fstream& is, SudokuGrid& gridIn){
    //this operator reads the class using the same format as is used in reading in a SudokuGrid object. inputs are SudokuGrid and output is fstream ( write in file)
    is >> gridIn.m_strGridName; //to pass "Grid ""
    is >> gridIn.m_strGridName; //to pass the the number
    //cout<<"gridIn.m_strGridName"<<gridIn.m_strGridName<<endl;
    for (int i = 0; i < N; i++){ //add elements to the file
        for (int j = 0; j < N ; j++){            
            is >> gridIn.gridElement[i][j];
        }
    }
    return is;
}

bool SudokuGrid::solve(){
    //solve one instance by calling SolveSudoku(intgridElement). Apart from that is covert from usnigned cha to int and vice versa.
    int intgridElement[N][N];
    for (int i = 0 ; i< N;  i++){
        for (int j = 0 ; j< N;  j++){
            intgridElement[i][j] = gridElement[i][j] - '0'; //since gridElement is unsigned char but the SolveSudoku needs integer. 

        }
    }
    if( SolveSudoku(intgridElement) == true){
        for (int i = 0 ; i< N;  i++){
            for (int j = 0 ; j< N;  j++){
                gridElement[i][j] = intgridElement[i][j] + '0'; // back from intiger to unsigned char!
            }
        }
        return true;
    }
    else{
        return false;
    }

}


void solveSudokuPuzzles(){
    
    SudokuGrid MySG;
    do{
        //make read fom file safe using mutext function: lock!
        inFileMutex.lock();
        inFile >> MySG; // Read from file.
        inFileMutex.unlock();

        if (MySG.solve() == true){ 
            //make write into file safe using mutext function: lock!
            outFileMutex.lock();
            outFile << MySG; //Write into file.
            outFileMutex.unlock();
        }        
    }while(!inFile.eof());

}


  
