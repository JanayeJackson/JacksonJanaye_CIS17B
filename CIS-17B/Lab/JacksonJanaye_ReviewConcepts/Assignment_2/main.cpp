/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 * Created on 2/22/2024 5:20 PM
 * Purpose:  Sorting a 2-D array of characters if row and columns match
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <cstring> //strlen(),strcmp(),strcpy()
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=80;//Only 20 required, and 1 for null terminator

//Function Prototypes Here
int  read(char [][COLMAX],int &);//Outputs row and columns detected from input
void sort(char [][COLMAX],int,int);//Sort by row
void print(const char [][COLMAX],int,int);//Print the sorted 2-D array

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=30;             //Only 20 required
    char array[ROW][COLMAX];      //Bigger than necessary 
    int colIn,colDet,rowIn,rowDet;//Row, Col input and detected
    
    //Input the size of the array you are sorting
    cout<<"Read in a 2 dimensional array of characters and sort by Row"<<endl;
    cout<<"Input the number of rows <= 20"<<endl;
    cin>>rowIn;
    cout<<"Input the maximum number of columns <=20"<<endl;
    cin>>colIn;
    
    //Now read in the array of characters and determine it's size
    rowDet=rowIn;
    cout<<"Now input the array."<<endl;
    colDet=read(array,rowDet);
    
    //Compare the size input vs. size detected and sort if same
    //Else output different size
    if(rowDet==rowIn&&colDet==colIn){
        sort(array,rowIn,colIn);
        cout<<"The Sorted Array"<<endl;
        print(array,rowIn,colIn);
    }else{
        if(rowDet!=rowIn)
        cout<<(rowDet<rowIn?"Row Input size less than specified.":
            "Row Input size greater than specified.")<<endl;
        if(colDet!=colIn)
        cout<<(colDet<colIn?"Column Input size less than specified.":
            "Column Input size greater than specified.")<<endl;
    }
    
    //Exit
    return 0;
}

int read(char inp[][COLMAX], int &row){
    int num = 0;
    row = 0;
    while(cin>>inp[row]){
        if(strlen(inp[row])>num)
            num = strlen(inp[row]);
        row++;
    }
    return num;
}
void sort(char inp[][COLMAX], int row, int col){
    char temp[col];
    
    for(int i = 0; i < row-1; i++ ){
        int indx = i;
        strcpy(temp, inp[i]);
        for(int n=i+1; n<row; n++){
            if(strcmp(inp[indx],inp[n])>0){
                strcpy(temp,inp[n]);
                indx=n;
            }
        }
        strcpy(inp[indx], inp[i]);
        strcpy(inp[i], temp);
    }
}
void print(const char inp[][COLMAX], int row, int col){
    for(int i = 0; i<row; i++){
        cout<<inp[i];
    cout<<endl;
    }
}
