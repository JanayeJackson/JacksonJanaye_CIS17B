/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 * Created on 2/23/2024 10:05 AM 
 * Purpose:  Input something, output it reversed with some modifications
 * Note:Range should be 5 digits, 321 = 00321 reverse = 12300 before subtraction
 *      12300 - 999 = 11301 after subtraction
 *      12300 = 00321 = 321 after reversal and no subtraction
 */

//System Libraries Here
#include <iostream>//cin,cout,endl
#include <cstring> //strlen()
using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
bool  inRange(const char [],unsigned short &);//Output true,unsigned or false
bool  reverse(unsigned short,signed short &);//Output true,short or false
short subtrct(signed short,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int SIZE=80;     //More than enough
    char  digits[SIZE];    //Character digits or not
    unsigned short unShort;//Unsigned short
    short snShort;         //Signed short
    
    //Input or initialize values Here
    cout<<"Reverse a number and subtract if possible."<<endl;
    cout<<"Input a number in the range of an unsigned short"<<endl;
    cin>>digits;
    
    //Test if it is in the Range of an unsigned short
    if(!inRange(digits,unShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Reverse and see if it falls in the range of an signed short
    if(!reverse(unShort,snShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Now subtract if the result is not negative else don't subtract
    snShort=subtrct(snShort,999);
    
    //Output the result
    cout<<snShort<<endl;
    
    //Exit
    return 0;
}

bool inRange(const char in[], unsigned short &num){
    int mul = 1;
    int add = strlen(in);
    num = 0;
    for(int i =0; i < add; i++){
        if(in[i] > 57 || in[i] < 48)
            return false;
        num += (in[add-i-1] - 48)*mul;
        mul *= 10;
    }
    if(num <65535){
        return true;
    }
    else
        return false;
}
bool reverse(unsigned short num, signed short &num2){
    int add, dvde, mul;
    add = 0;
    dvde = 10000;
    mul = 1;
    for(int i =0; i<5; i++){
        add += (num/dvde) * mul;
        num = num%dvde;
        dvde /= 10;
        mul *= 10;
    }
    
    if(add < 32767){
        num2 = add;
        return true;
    }
    else
        return false;
}
short subtrct(signed short num, int sub){
    if(num - sub < 0)
        return num;
    return num-sub;  
}