/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: Oct 13, 2020!!
Description: 
This program solves the the stream of Sudoku puzzles concurrently.  
The main function needs to dynamically determine the maximum number of threads that can run concurrently. 
The main() function should then spawn (numThreads-1) threads calling the function solveSudokuPuzzles().
I use online solutions for solving the individual Sudoku problem: https://www.geeksforgeeks.org/sudoku-backtracking-7/
MaxOS compile: clang++ -Xpreprocessor -fopenmp -I/usr/local/include -L/usr/local/lib -lomp  main.cpp 
Linux compile: g++ -std=c++11 mian.cpp -lpthread
*/
#pragma once

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
  

///Global variables
std::mutex outFileMutex;
std::mutex inFileMutex; 
std::fstream outFile;
std::fstream inFile;
// UNASSIGNED is used for empty 
// cells in sudoku grid 
#define UNASSIGNED 0 

// N is used for the size of Sudoku grid. 
// Size will be NxN 
#define N 9 
///End Global variables


class SudokuGrid{
    //Create a class called SudokuGrid that is used to hold a single puzzle with a constant 9 x 9 array ofunsigned char elements.

public: //member function of the class.
    friend fstream& operator>>(fstream& os,  SudokuGrid& gridIn);
    friend fstream& operator<<(fstream& is,  SudokuGrid& gridIn);
    bool solve();
    SudokuGrid();
private: //field of the class
    string m_strGridName;
    unsigned char gridElement[N][N];
};

