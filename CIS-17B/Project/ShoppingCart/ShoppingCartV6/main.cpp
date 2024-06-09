/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 *
 * Created on April 24th, 2024, 6:58 PM
 * Purpose: Create a shopping cart with a user and admin
 */

//System Level Libraries

#include <iostream>  //Input-Output Library
#include <string>
using namespace std;

//User Defined Libraries
#include "Admin.h"
#include "User.h"
#include "Login.h"

//Global Constants, not Global Variables
//These are recognized constants from the sciences
//Physics/Chemistry/Engineering and Conversions between
//systems of units

//Function Prototypes

//Execution begins here!
int main(int argc, char** argv) {
    //Initialize Random Seed once here!
    
    //Declare Variables
    char *user;
    char choice;
    bool match = false;
    
    user = new char[81];
    //Initialize Variables
    
    //Map the inputs/known to the outputs
    cout<<"Username: ";
    cin>>user;
    Login session(user);
    
    //Display the outputs
    
    //Exit the program

    return 0;
}

