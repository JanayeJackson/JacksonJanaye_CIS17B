/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 * Created on: 2/23/2024 2:31 PM
 * Purpose:  To tell the Truth
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int x,y;
    int input;
    
    //Display the Heading
    cout<<"X Y !X !Y X&&Y X||Y X^Y X^Y^X X^Y^Y !(X&&Y) !X||!Y "<<
          " !(X||Y) !X&&!Y"<<endl;
    
   while(cin>>input)
    {
        x = input; 
        cin>>y;
        
        //output truth table
        cout<<(x?'T':'F')<<" ";
        cout<<(y?'T':'F')<<"  ";
        cout<<(!x?'T':'F')<<"  ";
        cout<<(!y?'T':'F')<<"   ";
        cout<<(x&&y?'T':'F')<<"    ";
        cout<<(x||y?'T':'F')<<"   ";
        cout<<(x^y?'T':'F')<<"    ";
        cout<<((x^y)^x?'T':'F')<<"     ";
        cout<<((x^y)^y?'T':'F')<<"       ";
        cout<<(!(x&&y)?'T':'F')<<"      ";
        cout<<(!x||!y?'T':'F')<<"        ";
        cout<<(!(x||y)?'T':'F')<<"      ";
        cout<<(!x&&!y?'T':'F');
        cout<<endl;
    }
    cout<<endl;
    

    //Exit
    return 0;
}