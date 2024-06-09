/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 *
 * Created on 03/13/2023 11:40 PM
 * Purpose: Weather Database
 */

//System Level Libraries

#include <iostream>  //Input-Output Library
#include <iomanip>
using namespace std;

//User Defined Libraries

//Global Constants, not Global Variables
//These are recognized constants from the sciences
//Physics/Chemistry/Engineering and Conversions between
//systems of units

//structures
struct Weather{
    string month;
    int tRain;
    int hTemp;
    int lTemp;
    float aTemp;
};

//Function Prototypes


//Execution begins here!
int main(int argc, char** argv) {
    //Initialize Random Seed once here!
    
    //Declare Variables
    int size = 12;
    int lIndx, hIndx = 0;
    int high, low;
    float avgRain, avgTemp;
    Weather wData [size];
    
    
    //Initialize Variables
    
    //Map the inputs/known to the outputs
    for(int i = 0; i < size; i++)
    {
        cin>>wData[i].month
        >>wData[i].tRain
        >>wData[i].lTemp
        >>wData[i].hTemp;
        wData[i].aTemp = (wData[i].hTemp + wData[i].lTemp)/2.0;
        
        avgRain += wData[i].tRain;
        avgTemp += wData[i].aTemp;
    }
    
    high = wData[0].hTemp;
    low = wData[0].lTemp;
    
    for(int i = 1; i < size; i++){
        if(wData[i].hTemp > high)
        {
            high = wData[i].hTemp;
            hIndx = i;
        }
        
        if(wData[i].lTemp < low)
        {
            low = wData[i].lTemp;
            lIndx = i;
        }
        
    }
    
    avgRain /= 12;
    avgTemp /= 12;
    
    //Display the outputs
    cout<<"Average Rainfall "<<setprecision(2)<<avgRain<<" inches/month"<<endl;
    cout<<"Lowest  Temperature "<<wData[lIndx].month<<"  "<<wData[lIndx].lTemp<<" Degrees Fahrenheit"<<endl;
    cout<<"Highest Temperature "<<wData[hIndx].month<<"  "<<wData[hIndx].hTemp<<" Degrees Fahrenheit"<<endl;
    cout<<"Average Temperature for the year "<<avgTemp<<" Degrees Fahrenheit"<<endl;
    
    //Exit the program

    return 0;
}