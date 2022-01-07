/*
Author: Payman Behnam Class: ECE 6122-A
Last Date Modified: 903154319
Description: Aug 31, 2020!!
I, your name , have successfully accessed my pace-ice account. 
I am able to transfer files from my pace-ice account to my local machine using an ftp client. 
I am ready for the next assignment on pace-ice.
*/

#include <iostream>

int main(){
    using namespace std; //“using namespace std” means we use the namespace standard. Instead of that we can use std::cout, std::endl in this namespace!
    //cout << "My name is: Payman Behnam" << endl; Just to show we can use "endl" instead of "\n". The escape sequence \n means newline.
    
    cout << "My name is: Payman Behnam\n";     //The backslash (\) is called an escape character.
    cout << "This (\') is a single quote.\n"; // Single quote should work fine even without \. 
    cout << "This (\") is a double quote.\n"; // \ is a way to indicate that the following character (or characters) are special
    cout << "This (/) is a forward slash.\n";
    cout << "This (\\) is a backslash.\n";

    return 0;
}