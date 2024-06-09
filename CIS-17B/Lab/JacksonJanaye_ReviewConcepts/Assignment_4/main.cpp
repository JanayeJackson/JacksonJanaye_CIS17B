/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 * Created on 2/22/2024 7:53 PM
 * Purpose:  Even, Odd Vectors and Array Columns Even, Odd
 * Note:  Check out content of Sample conditions in Hacker Rank
 * Input size of integer array, then array, output columns of Even, Odd
 * Vectors then Even, Odd 2-D Array
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <vector>  //vectors<>
#include <iomanip> //Format setw(),right
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=2;//Only 2 columns needed, even and odd

//Function Prototypes Here
void read(vector<int> &, vector<int> &);
void copy(vector<int>, vector<int>,int [][COLMAX]);
void prntVec(vector<int>, vector<int>,int);//int n is the format setw(n)
void prntAry(const int [][COLMAX],int,int,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=80;           //No more than 80 rows
    int array[ROW][COLMAX];     //Really, just an 80x2 array, even vs. odd
    vector<int> even(0),odd(0); //Declare even,odd vectors
    
    //Input data and place even in one vector odd in the other
    read(even,odd);
    
    //Now output the content of the vectors
    //          setw(10)
    prntVec(even,odd,10);//Input even, odd vectors with setw(10);
    
    //Copy the vectors into the 2 dimensional array
    copy(even,odd,array);
    
    //Now output the content of the array
    //                              setw(10)
    prntAry(array,even.size(),odd.size(),10);//Same format as even/odd vectors*/
    
    //Exit
    return 0;
}

void read(vector<int> &even, vector<int> &odd){
    int num, size;
    cout<<"Input the number of integers to input."<<endl;
    cin>>size;
    cout<<"Input each number."<<endl;
    for(int i=0; i<size; i++){
        cin>>num;
        if(num %2 == 0)
            even.push_back(num);
        else
            odd.push_back(num);
    }
}
void copy(vector <int> even, vector<int> odd, int arr[][COLMAX]){
    
    for(int i=0; i<even.size(); i++){
        arr[i][0] = even[i];
    }
    for(int i=0; i<odd.size(); i++ ){
        arr[i][1] = odd[i];
    }
    
    
}
void prntVec(vector<int> even, vector<int> odd, int num){
    int size; 
    cout<<"    Vector      Even       Odd"<<endl;
    if(even.size()>odd.size()){
        size=even.size();
        for(int i=0; i<size; i++){
            if(i > odd.size() -1)
                cout<<setw(num)<<" "<<setw(num)<<even[i]<<setw(num)<<" "<<endl;
            else
                cout<<setw(num)<<" "<<setw(num)<<even[i]<<setw(num)<<odd[i]<<endl;
            
        }
    }
    else{
        size=odd.size();
        for(int i=0; i<size; i++){
            if(i > even.size() -1)
                cout<<setw(num)<<" "<<setw(num)<<" "<<setw(num)<<odd[i]<<endl;
            else
                cout<<setw(num)<<" "<<setw(num)<<even[i]<<setw(num)<<odd[i]<<endl;
            
        }
    }
   
}
void prntAry(const int arr[][COLMAX], int eSize, int oSize, int num){
    int size;
    cout<<"     Array      Even       Odd"<<endl;
    if(eSize > oSize){
        size = eSize;
        for(int i=0; i<size; i++){
            if(i > oSize -1)
                cout<<setw(num)<<" "<<setw(num)<<arr[i][0]<<setw(num)<<" "<<endl;
            else
                cout<<setw(num)<<" "<<setw(num)<<arr[i][0]<<setw(num)<<arr[i][1]<<endl;
        }
    }
    else{
        size = oSize;
        for(int i=0; i<size; i++){
            if(i > eSize-1)
                cout<<setw(num)<<" "<<setw(num)<<" "<<setw(num)<<arr[i][1]<<endl;
            else
                cout<<setw(num)<<" "<<setw(num)<<arr[i][0]<<setw(num)<<arr[i][1]<<endl;
        }
    }
}