/* 
 * File:   main.cpp 
 * Author: Janaye Jackson   
 * Created on 03/13/2024 6:11 pm
 * Purpose:  
 */

//System Libraries
#include <iostream>
#include<iomanip>
using namespace std;

//User Libraries

//Global Constants - No Global Variables
//Only Universal Constants, Math, Physics, Conversions, Higher Dimensions

//enumartor
enum Month {JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY,
            AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};
            
//structures
struct Weather{
    int hTemp;
    int lTemp;
    float rain;
    float aTemp;
    
};

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Set Random Number seed
    
    //Declare Variable Data Types and Constants
    int hTemp, lTemp = 0;
    float aTemp, aRain = 0.0;
    Weather wData [JUNE + 1];
    
    //Initialize Variables
    for(int i = 0; i <= JUNE; i++)
    {
        cout<<"Enter the total rainfall for the month:"<<endl;
        cin>>wData[i].rain;
        cout<<"Enter the high temp:"<<endl;
        cin>>wData[i].hTemp;
        cout<<"Enter the low temp:"<<endl;
        cin>>wData[i].lTemp;
        
        wData[i].aTemp += (wData[i].hTemp + wData[i].lTemp)/2.0;
        aTemp += wData[i].aTemp;
        aRain += wData[i].rain;
    }
    
    hTemp = wData[0].hTemp;
    lTemp = wData[0].lTemp;
    
    for(int i = 0; i <= JUNE; i++)
    {
        if(wData[i].hTemp > hTemp)
            hTemp = wData[i].hTemp;
        if(wData[i].lTemp < lTemp)
            lTemp = wData[i].lTemp;
    }
    
    //Process or map Inputs to Outputs
    aRain /= (JUNE + 1);
    aTemp /= (JUNE+1);
    
    //Display Outputs
    cout<<"Average monthly rainfall:"<<fixed<<setprecision(2)<<aRain<<endl;
    cout<<"High Temp:"<<hTemp<<endl;
    cout<<"Low Temp:"<<lTemp<<endl;
    cout<<"Average Temp:"<<fixed<<setprecision(1)<<aTemp;

    //Exit stage right!
    return 0;
}