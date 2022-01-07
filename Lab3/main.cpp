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
#include "Lab3_Problem1.cpp" 
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
  



// Driver Code 
int main(int argc, char *argv[]){ 

    inFile = fstream (argv[1], fstream::in); 
	if (!inFile) {//check validty if input exist
    	cout << "Error, file couldn't be opened" << endl; 
    	exit(1); 
    }
    outFile = fstream("Lab3Prob1.txt", fstream::out); // create outputfile
    
    
    
    //auto start2 = high_resolution_clock::now(); // capture start time;

    unsigned int nThreads = std::thread::hardware_concurrency()-1; //// ardware_concurrency: Return value is Number of concurrent threads supported. If the value is not well defined or not computable, returns ​0​.

    //vector<std::thread> threadVec;
    //if (nThreads >0){
    vector<std::thread>  threadVec(nThreads);
    //}
    //else{
    //    cout<< "There is no enough thread to run in parallel"<<endl;
    //    exit(1);
    //}


    for (int i = 0; i < nThreads; ++i)//spawn (numThreads-1) threads calling the function solveSudokuPuzzles().
        threadVec[i] = thread (solveSudokuPuzzles);
    
    for (int i = 0; i < nThreads; ++i)// join all spawn threads
        threadVec[i].join();
    
    //auto stop2 = high_resolution_clock::now(); // capture stop time
    //auto duration2 = duration_cast<microseconds>(stop2 - start2);// capture duration
    //cout << "parallel exeuction time in ms = " << duration2.count() << endl; //print timing.
    
    //close the opened files
    outFile.close();
    inFile.close();
   
    
    
    return 0; 
} 
  
