/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 * Created on 03/13/2024 5:50 pm
 * Purpose:  Create structure for sales and display the annual and average quarterly sales
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants - No Global Variables
//Only Universal Constants, Math, Physics, Conversions, Higher Dimensions

//Strucures
struct Sales{
    float fQtr, sQtr, tQtr, fthQtr;
};

//Function Prototypes
void print(Sales);



//Execution Begins Here
int main(int argc, char** argv) {
    //Set Random Number seed
    
    //Declare Variable Data Types and Constants
    Sales north, west, east, south;
    
    //Initialize Variables
    
    //Process or map Inputs to Outputs
    
    //Display Outputs
    cout<<"North"<<endl;
    print(north);
    cout<<"\nWest"<<endl;
    print(west);
    cout<<"\nEast"<<endl;
    print(east);
    cout<<"\nSouth"<<endl;
    print(south);

    //Exit stage right!
    return 0;
}

void print(Sales rgn)
{
    float sum, avg;
    sum = 0;
    avg = 0;
    
    cout<<"Enter first-quarter sales:"<<endl;
    cout<<"Enter second-quarter sales:"<<endl;
    cout<<"Enter third-quarter sales:"<<endl;
    cout<<"Enter fourth-quarter sales:"<<endl;
    cin>>rgn.fQtr>>rgn.sQtr>>rgn.tQtr>>rgn.fthQtr;
    
    sum = rgn.fQtr + rgn.sQtr+ rgn.tQtr + rgn.fthQtr;
    avg = sum/4;
    cout<<"Total Annual sales:$"<<showpoint<<setprecision(6)<<sum<<endl;
    cout<<"Average Quarterly Sales:$"<<avg;
}