/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 * Created on 2/23/2024 10:56 AM 
 * Note:  This time you create the strcmp() function that takes into
 * account the new sort order.
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <cstring> //strlen(),strcmp(),strcpy()
using namespace std;

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=80;//Only 20 required, and 1 for null terminator

//Function Prototypes Here
int  read(char [][COLMAX],int &);//Outputs row and columns detected from input
void sort(char [][COLMAX],int,int,const char[],const char[]);//Sort by row using strcmp();
void print(const char [][COLMAX],int,int);//Print the sorted 2-D array
//int strcmp(char a[],char b[],char replace[],char with[]){
int strcmp(char [],char [],const char [],const char []);//Replace sort order

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=30;             //Only 20 required
    char array[ROW][COLMAX];      //Bigger than necessary 
    int colIn,colDet,rowIn,rowDet;//Row, Col input and detected
    char replace[COLMAX],with[COLMAX];//New sort order
    
    //Input the new sort order then sort
    cout<<"Modify the sort order by swapping these characters."<<endl;
    cin>>replace;
    cout<<"With the following characters"<<endl;
    cin>>with;
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
    //if(rowDet==rowIn&&colDet==colIn){
        sort(array,rowIn,colIn,replace,with);
        cout<<"The Sorted Array"<<endl;
        print(array,rowIn,colIn);
    
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
void sort(char inp[][COLMAX], int row, int col, const char rep[], const char with[]){
    char temp[col];
    
    for(int i = 0; i < row-1; i++ ){
        int indx = i;
        strcpy(temp, inp[i]);
        for(int n=i+1; n<row; n++){
            if(strcmp(inp[indx],inp[n], rep, with)<0){
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

int strcmp(char a[],char b[],const char rep[],const char with[]){
    int num = 0; 
    
    if(strlen(a) < strlen(b))
        num = strlen(a);
    else
        num = strlen(b);
    char temp1[num], temp2[num];
    
    for(int i =0; i < num; i++){
        temp1[i] = a[i];
        temp2[i] = b[i];
    }
    
    for(int i = 0; i < strlen(rep); i++){
        for(int n = 0; n < num; n++){
            if(rep[i] == a[n]){
                temp1[n] = with[i];
            }
            if(rep[i] == b[n]){
                temp2[n] = with[i];
            }
            if(with[i] == a[n]){
                temp1[n] = rep[i];
            }
            if(with[i] == b[n]){
                temp2[n] = rep[i];
            }
        }
    }
    for(int i = 0; i < num; i++){
        if(temp1[i] < temp2[i])
            return 1;
        else if (temp1[i] > temp2[i])
            return -1;
    }
    return 0;
    
}