/*
Author: Payman Behnam Class: ECE 6122-A, 903154319
Last Date Modified: Sep 13, 2020!!
Description:  Calculate the sum of the resulting Collatz Sequence
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
   
*/

#include <iostream>
#include <fstream>
#include <climits>

using namespace std; 
  
bool isEven(unsigned long int lNum){      
    if (lNum % 2 == 0) // check if the number is even 
        return true; 
    else
        return false; 
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
    
    unsigned long int index = stoul(argv[1]);
    unsigned long int sum = index;
       
    while (index != 1 ){ //generate a Collatz sequence and sum of them
        if (isEven(index)){ 
            index = index / 2; // Even case
        }
        else{
            index = 3 * index + 1; // Odd case
        }
        
        sum = sum + index;  // Sum of generated Collatz sequence
    }
    
    //write the results into file
    ofstream myfile;
    myfile.open ("output2.txt");
    myfile << sum;
    myfile.close();
    
    return 0;
    
}