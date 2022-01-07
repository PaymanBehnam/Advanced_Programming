
/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: OCT 13, 2020!!
Description: 
calculate the sum of the prime numbers less than or equal to this input value
Use OpenMP to create a multi-threaded program that uses the fundamental theory and logic of the Monte Carlo Simulation technique to solve the following optimization problem:
𝑍 = (𝑒^𝑋1 + 𝑋2)^2 + 3(1 − 𝑋3)^2
Find the values of X1, X2, and X3 such that the following equation has the maximum value for Z.
Subject to:
0 ≤ X1 ≤ 1
0 ≤ X2 ≤ 2
2 ≤ X3 ≤ 3

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
#include <omp.h>
//#include "/usr/local/opt/libomp/include/omp.h" //For run in Mac
#include <chrono>
#include <thread>
#include <mutex>
#include <iomanip> 
//using namespace std::chrono; //for time measuring

using namespace std; 


int main (int argc, char * argv[]){

    //long trial= 1;
    unsigned int nThreads = std::thread::hardware_concurrency(); // Return value is Number of concurrent threads supported. If the value is not well defined or not computable, returns ​0​.
    long maxtrial;
    double  maxz=0; // because from the function we know z will not be negative
    double  x1final, x2final, x3final; //keep updated final values
    fstream myfile;
    if (argc != 2){
        cout << "In correct usage: you should type ./a.out N"<<endl;
        exit(1);
    }
    else{
        maxtrial = atoi(argv[1]);
    }

    
   // auto start2 = high_resolution_clock::now(); // capture start time

    
    #pragma omp parallel default(none) shared( x1final, x2final, x3final, maxz, maxtrial) num_threads(nThreads) 
    // Here we define the parameetrs that need to be shared. other than that, they are private
    //so, each thread has a copy of x1,x2,x3, distributionxi, and z with correponding values
    {
    double  x1, x2, x3, z;
    
    //using c++ libraries to generete x in the specific intervals.
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distributionx1(0 , 1);
    std::uniform_real_distribution<double> distributionx2(0 , 2);
    std::uniform_real_distribution<double> distributionx3(2 , 3);
    //#pragma omp parallel for : It was useful for very large N in some runs.
    for (long trial =1;  trial <= maxtrial; trial++){
        //Generate xi values
        x1= distributionx1(generator); 
        x2= distributionx2(generator);
        x3= distributionx3(generator);
        

        z = pow( exp(x1) + x2 , 2) + 3 * pow(1 - x3, 2);
        //#pragma omp reduction(max:z) num_threads(nThreads)
        #pragma omp critical // here we need to find the current max value between all threads and keep corresponding xi values.
        //So, we have to deifine critical section and let threads to check the value one by one to make sure we keep the max value correctly.
        {
            if ( z > maxz ){
                x1final = x1; x2final = x2; x3final = x3; maxz= z;
            }
        }
    }    
    }
    // auto stop2 = high_resolution_clock::now(); //capture stop time
    //auto duration2 = duration_cast<microseconds>(stop2 - start2); // time measurement.
    //cout << "exeuction time = " << duration2.count() << endl; //print timing
    myfile = fstream("Lab3Prob3.txt", fstream::out); //open the file
    //myfile.open ("Lab3Prob3.txt");
    //Print values in file //write out to 15 decimal places to the text file
    myfile << std::fixed <<std::setprecision (15)<< x1final <<endl;
    myfile << std::fixed <<std::setprecision (15)<< x2final <<endl;
    myfile << std::fixed <<std::setprecision (15)<< x3final <<endl;
    //myfile << std::fixed <<std::setprecision (15)<< maxz <<endl; //Print the max value in file. 
    myfile.close();

}