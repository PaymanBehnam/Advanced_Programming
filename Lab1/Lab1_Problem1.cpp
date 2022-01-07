/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: Oct 13, 2020!!
Description: 
calculate the sum of the prime numbers less than or equal to this input value
NOTE: as the problem asked us to use argc and argv I am checking validity of the input using them. However, the better way is using the following way
    
#include <iostream>
#include <sstream>
#include <cstdint>

int main() {
    uint64_t value;
    std::istringstream iss("1164343534534345344354310");
    iss >> value;
    std::cout << (iss.fail() ? "Failed" : "Succeeded!") << std::endl;
    std::cout << value;
   
}
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>

using namespace std; 
  
bool isPrime(unsigned long int lNum){      
    if (lNum <= 1) // Corner cases
        return false; 
    for (unsigned long int i = 2; i < lNum; i++) // Check if the number has any divisor from 2 to n-1 
        if (lNum % i == 0) 
            return false; 
    return true; 
} 
bool isNumber(string str){ 
    for (unsigned long int  j = 0; j < str.length(); j++) 
        if (isdigit(str[j]) == false) 
            return false; 
  
    return true; 
} 
  

int main(int argc, char* argv[]){
    // Check the number of parameters and if the input number is unsigned long int
    if ( argc < 2||  !isNumber(argv[1])  ||  stoull(argv[1]) > ULONG_MAX || stoul(argv[1]) <= 0 ) {
        // Tell the user how to run the program
       
        cerr << "Usage:'' " << argv[0] << " NUMBER: ''Enter an unsigned long int number (1 to 18446744073709551615) with name of the program (e.g. ./a.out 5)" << endl;
        return 1;
    }
    
    unsigned long int sum = 0;
    for (unsigned long int i = 2; i <= stoul(argv[1]); i++){ //compute the sum of prime numbers
         
        if (isPrime(i)){ 
             sum = sum + i;
        }
    }
    
    //write the results into file
    ofstream myfile;
    myfile.open ("output1.txt");
    myfile << sum;
    myfile.close();
    
    return 0;
    
}