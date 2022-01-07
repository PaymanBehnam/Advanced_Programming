/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: OCT 13, 2020!!
Description: 
Another ant on the move problem  (https://brilliant.org/practice/monte-carlo/)
We define 2D array <gxg> with all values zero and four moves: up=>1,down=>2,left=>3,right=>4. Each time that we got o new cell, that cell becomes '1'.
We go to one of the cells (that there is possibility (e.g., no out of range) or not visited previously) with a specific probability. 
Each thread tries to find a path independetly. However, updating number of found or not found 
paths should be done through defining critical section and uodate those variables one by one. 
NOTE:
To make the parallel algorithm faster, I tried "malloc" of the developed
*library by Google:
*http://pages.cs.wisc.edu/~danb/google-perftools-0.98/tcmalloc.html
Apperantly, "new" in C++ (posix) is not developed efficiently. Hence,
Intel and Google developed efficient library for it.I am not sure we are allow to use this library to make tun time faster. so, I didnt incorporate in the tool.!
*/
 
#include <fstream> 
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <climits>
#include <stdlib.h>     
#include <random>
#include <string.h>
#include <omp.h>
//#include "/usr/local/opt/libomp/include/omp.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip> 
#include <chrono>
//using namespace std::chrono; //for time measuring
using namespace std; 

int main (int argc, char * argv[]){
    long maxtrial = 10;
    long dim = 6;
    //checking input
    if (argc != 5){
        cout <<"incorret usage: please follow ./a.out -N 100000 -g 6 OR  ./a.out -g 6 -N 100000 "<<endl;
    }
    if (strcmp(argv[1], "-N") == 0 &&  strcmp(argv[3], "-g") == 0){
        maxtrial = atoi(argv[2]);
        dim = atoi(argv[4]);
    }
    else if (strcmp(argv[1], "-g") == 0 &&  strcmp(argv[3], "-N") == 0){
        maxtrial = atoi(argv[4]);
        dim = atoi(argv[2]);

    }
    else {
        cout <<"incorret usage: please follow ./a.out -N 100000 -g 6 OR  ./a.out -g 6 -N 100000"<<endl;
        exit(1);
    }
    
    long pathFound = 0;// counter for number of cases where we reach to the final point. 
    long stuck = 0; //  counter for number of cases where we dont reach to the final point.
    
    

    unsigned int nThreads = std::thread::hardware_concurrency(); //// Return value is Number of concurrent threads supported. If the value is not well defined or not computable, returns ​0​.

    //auto start2 = high_resolution_clock::now(); //// capture start time
    #pragma omp parallel default(none) shared(stuck, pathFound, maxtrial, dim)  num_threads(nThreads)
    {
    // Here we define the parameetrs that need to be shared. other than that, they are private
    //so, each thread has a copy of coordListm, up,down,left,right,  random, i, j, and flag. 
    int **coordList = new int*[dim]; //2d array of size for the grid //
    int up=0, right=0, down=0, left=0 ;
    int rand = 0; 
    long i = 0; // index for walking into rows
    long j = 0; // index for walking into columns
    bool flag = false; // used to check if the random move is the one that we potentially can go there,
   
    
    for (long trial = 0; trial < maxtrial; trial++){
        
        //#pragma omp parallel for schedule(dynamic) //schedule(guided,1) This optimization doesnot create that much benefit due to limited # threads.
        for (int row = 0; row < dim; row++){ //for each iteration for each thread we make all elemets zero to create a fresh copy. I tried 1-d Array also. For this specifc problem it didnt generate better results.
            coordList[row] = new int[dim];
            for (int col = 0; col < dim; col++){
                coordList[row][col] = 0;
            }
        }   
        
        while (true) { 
                
            //check possibilities of all the moves
            if ( i - 1 != -1 ){ //check border
                if (coordList[i - 1][j] == 0){ //check if not visited
                    up = 1; 
                }
            }

            if ( i + 1 != dim ){
                if (coordList[i + 1][j] == 0){
                    down = 1; 
                }
            }

            if ( j - 1 != -1 ){
                if (coordList[i][j - 1] == 0){
                    left = 1; 
                }
            }
            
            if ( j + 1 != dim ){
                if (coordList[i][j+1] == 0){
                    right = 1; 
                }
            }
  
        
            if (up == 0 && right == 0 &&  down == 0 && left == 0){ // if there is no possibility we are stuck!
                #pragma omp critical
                {
                stuck += 1; ////needs to be updated in critical section.
                }
                i = j = 0;
                up = right = down = left = 0; 
                break;
            
            }
            //where up=>1,down=>2,left=>3,right=>4.
            
            //Generate random variable. I used different method than probem3.
            //std::default_random_engine generator;
            //std::uniform_int_distribution<int> distribution(1,4);
            //rand = distribution(generator);
            std::random_device rd;  //Will be used to obtain a seed for the random number engine
            std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
            //specify the range
            std::uniform_int_distribution<> distrib(1, 4);
            
            do{
            flag = false;
            rand = distrib(gen); //  generate random variable
            if (rand==1 && up == 0) flag = true;  // if up=0 but rand say we need to go up, we should ignore and generate new rand. Same thing for others. flag is used to check this in a while-loop.
            else if (rand==2 && down == 0) flag = true;
            else if (rand==3 && left == 0) flag = true;
            else if (rand==4 && right == 0) flag = true;
            } while(flag == true);
            
            //following ifs: update the cell with the move(i.e., make it 1); update corresponding index; make all up,down,left,right zero for the next move
            if(rand == 1) {
                    coordList[i - 1][j] = 1; 
                    i -= 1; 
                    up = right = down = left = 0; 
            }
            else if(rand == 2) {
                    coordList[i + 1][j] = 1;
                    i+=1;
                    up = right = down = left = 0;
            }
            else if(rand == 3) {
                    coordList[i][j - 1] = 1;
                    j -= 1;
                    up = right = down = left = 0;
            }
            else if(rand == 4) {
                    coordList[i][j+1] = 1;
                    j += 1;
                    up = right = down = left = 0;
            }
            
            if (i == dim-1 && j == dim-1){ //reach final point
                #pragma omp critical
                {
                pathFound += 1; //needs to be updated in critical section.
                }
                i = j = 0;
                up = right = down = left = 0;
                break;         
            }
        }
        //cout<<"pay6"<<endl; 
    }
    }
    //auto stop2 = high_resolution_clock::now(); ////capture stop time
    //auto duration2 = duration_cast<microseconds>(stop2 - start2); //// time measurement.
    //cout << "exeuction time  = " << duration2.count() << endl; //print timing
    //cout <<  "Probability::"<< (float)(pathFound)/(float)(pathFound+stuck) <<endl;

    ofstream myfile;
    myfile.open ("Lab3Prob2.txt"); //openfile
    //myfile << std::fixed <<std::setprecision (7)<< (float)(pathFound) <<endl;
    //myfile << std::fixed <<std::setprecision (7)<< (float)(pathFound+stuck) <<endl;
    myfile << std::fixed <<std::setprecision (7)<< (float)(pathFound)/(float)(pathFound+stuck) <<endl;  //write out the probability to 7 decimal places to the text file
    myfile.close();

}