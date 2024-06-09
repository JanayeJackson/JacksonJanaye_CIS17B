/* 
 * File:   Dice.cpp
 * Author: Janaye Jackson
 * Created on April 28th, 2024, 7:40 PM
 * Purpose:  To create and display faces of a dice
 */
//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Dice.h"

//Global Constants, physical, mathematical, conversions only

//Function Prototypes
Dice **filFace(int);                //Fill a die with faces
int   *filIndx(int);                //Fill an index to the faces
void   prntFace(Dice**,int *,int);  //Print the faces with an index

//Execution Begins Here
int main(int argc, char** argv) {   
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    int    nFaces=6;
    int  *index;
    Dice **face;
  
    //Initialize the data
    face=filFace(nFaces);
    index=filIndx(nFaces);
    
    //Print the Faces of a die
    cout<<"Faces of a die"<<endl;
    prntFace(face,index,nFaces);
    
    
    //Clean up memory allocation
    for(int i=0;i<nFaces;i++){
        delete face[i];
    }
    delete []face;
    delete []index;

    //Exit program stage right
    return 0;
}

void   prntFace(Dice **Face,int *indx,int n){
    for(int i=0;i<n;i++){
        cout<<Face[indx[i]]->toString();
    }
}

int   *filIndx(int n){
    int *indx=new int[n];
    for(int i=0;i<n;i++){
        indx[i]=i;
    }
    return indx;
}

Dice **filFace(int n){
    Dice **Face=new Dice*[n];
    for(int i=0;i<n;i++){
        Face[i]=new Dice(i);
    }
    return Face;
}