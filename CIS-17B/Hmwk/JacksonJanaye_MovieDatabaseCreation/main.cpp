/* 
 * Author: Janaye Jackson
 * Created on 03/17/2024
 * Purpose: Movie Data Structure
 */

//System Level Libraries
#include <iostream>   //I/O Library
using namespace std;  //Libraries compiled under std

#include <cstdlib>    //Random Number Generator, Setting seed, etc....
#include <iomanip>    //Formatting Library
#include <string>     //String Library
#include <fstream>
#include <ctime>
//User Level Libraries/Includes
#include "CMovie.h"

//Global Constants Only - Science/Math Related, Conversions, Array and Higher
//Dimensions.

//Function Prototypes here, Function implementations after main!


//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Open the Text and binary files
     //Variable Declarations
    CMovie cmovie;//Class
    int record = rand()%100;
    //Now you can loop on the data as many times as it takes!
    cmovie.display();
    cmovie.readInAll();//Look and see
    MovieInfo *a = cmovie.readIn(record);
    cout<<a->movName<<endl;
    cout<<a->dirName<<endl;
    cout<<a->yrRlsd<<endl;
    cout<<a->runTime<<endl;
    //Exit stage right!
    return 0;
}