/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 *
 * Created on 03/13/2023 11:12 PM
 * Purpose: Movie Database
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
struct Movies{
    string title;
    string drctr;
    int year;
    int rTime;
};

//Function Prototypes


//Execution begins here!
int main(int argc, char** argv) {
    //Initialize Random Seed once here!
    
    //Declare Variables
    int size;
    string temp;
    
    
    //Initialize Variables
    
    //Map the inputs/known to the outputs
    cout<<"This program reviews structures"<<endl;
	cout<<"Input how many movies, the Title of the Movie, Director, Year Released, and the Running Time in (minutes)."<<endl;
	getline(cin, temp);
	size = stoi(temp);
	Movies mData [size];
    
    //Display the outputs
    for(int i = 0; i < size; i++)
    {
        getline(cin, mData[i].title);
        getline(cin, mData[i].drctr);
        getline(cin, temp);
        mData[i].year = stoi(temp);
        getline(cin, temp);
        mData[i].rTime = stoi(temp);
    }
    
    for(int i = 0; i < size; i++){
        cout<<endl;
        cout<<left<<setw(11)<<"Title:"<<mData[i].title<<endl;
        cout<<left<<setw(11)<<"Director:"<<mData[i].drctr<<endl;
        cout<<left<<setw(11)<<"Year:"<<mData[i].year<<endl;
        cout<<left<<setw(11)<<"Length:"<<mData[i].rTime<<endl;
    }
    
    //Exit the program

    return 0;
}