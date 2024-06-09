/* 
 * File:  main.cpp 
 * Author: Janaye Jackson
 * Created on 3/13/2024 7:45 pm
 * Purpose:  Create a budget structure and determine if user has gone over or under budget
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//User Libraries

//Global Constants - No Global Variables
//Only Universal Constants, Math, Physics, Conversions, Higher Dimensions

//Structures

struct Budget{//structure to hold budget information
    float hse;
    float utl;
    float hExpns;
    float tsptn;
    float food; 
    float mdcl; 
    float ins; 
    float Etnmnt;
    float clths; 
    float misc;  
};
//Function Prototypes
Budget spend(); //gets amounts spent in each budget category during a month from user
void report(Budget, Budget); //reports statistics of information
string EUO(float, float);  //determine if budget is over under or even

//Execution Begins Here
int main(int argc, char** argv) {
    //Set Random Number seed
    
    //Declare Variable Data Types and Constants
    Budget stdnt, bdgt;
    
    //Initialize Variables
    bdgt.hse = 500.00;
    bdgt.utl = 150.00;
    bdgt.hExpns = 65.00;
    bdgt.tsptn = 50.00;
    bdgt.food = 250.00;
    bdgt.mdcl = 30.00;
    bdgt.ins = 100.00;
    bdgt.Etnmnt = 150.00;
    bdgt.clths = 75.00;
    bdgt.misc = 50.00;
    
    //Process or map Inputs to Outputs
    stdnt = spend();
    report(stdnt, bdgt);
    //Display Outputs

    //Exit stage right!
    return 0;
}

Budget spend(){
    //total spent
    Budget stdnt;
    
    //Ask user for unformation
    cout<<"Enter housing cost for the month:$"<<endl;
    cout<<"Enter utilities cost for the month:$"<<endl;
    cout<<"Enter household expenses cost for the month:$"<<endl;
    cout<<"Enter transportation cost for the month:$"<<endl;
    cout<<"Enter food cost for the month:$"<<endl;
    cout<<"Enter medical cost for the month:$"<<endl;
    cout<<"Enter insurance cost for the month:$"<<endl;
    cout<<"Enter entertainment cost for the month:$"<<endl;
    cout<<"Enter clothing cost for the month:$"<<endl;
    cout<<"Enter miscellaneous cost for the month:$"<<endl;
    
    //Get user input
    cin>>stdnt.hse
    >>stdnt.utl
    >>stdnt.hExpns
    >>stdnt.tsptn
    >>stdnt.food 
    >>stdnt.mdcl 
    >>stdnt.ins
    >>stdnt.Etnmnt
    >>stdnt.clths 
    >>stdnt.misc;
    
    return stdnt;
    
}

string EUO(float stdnt, float bdgt)
{
    if(stdnt>bdgt)
        return "Over";
    else if(stdnt<bdgt)
        return"Under";
    else
        return"Even";
}

void report(Budget student, Budget bdgt){
    float tSpnt, tBdgt, dffrnc;
    string ovUn;
    
    
    tSpnt = student.hse
    +student.utl
    +student.hExpns
    +student.tsptn
    +student.food 
    +student.mdcl 
    +student.ins
    +student.Etnmnt
    +student.clths 
    +student.misc;
    
    tBdgt = bdgt.hse
    +bdgt.utl
    +bdgt.hExpns
    +bdgt.tsptn
    +bdgt.food 
    +bdgt.mdcl 
    +bdgt.ins
    +bdgt.Etnmnt
    +bdgt.clths 
    +bdgt.misc;
    
    

    cout<<"Housing "<<EUO(student.hse, bdgt.hse)<<endl;
    cout<<"Utilities "<<EUO(student.utl, bdgt.utl)<<endl;
    cout<<"Household Expenses "<<EUO(student.hExpns, bdgt.hExpns)<<endl;
    cout<<"Transportation "<<EUO(student.tsptn, bdgt.tsptn)<<endl;
    cout<<"Food "<<EUO(student.food, bdgt.food)<<endl;
    cout<<"Medical "<<EUO(student.mdcl, bdgt.mdcl)<<endl;
    cout<<"Insurance "<<EUO(student.ins, bdgt.ins)<<endl;
    cout<<"Entertainment "<<EUO(student.Etnmnt, bdgt.Etnmnt)<<endl;
    cout<<"Clothing "<<EUO(student.clths, bdgt.clths)<<endl;
    cout<<"Miscellaneous "<<EUO(student.misc, bdgt.misc)<<endl;
    
    if(tSpnt >= tBdgt)
    {
        cout<<"You were $"<<fixed<<setprecision(2)<<tSpnt - tBdgt<<" over budget";
    }
    if(tSpnt < tBdgt)
    {
        cout<<"You were $"<<fixed<<setprecision(2)<<tBdgt - tSpnt<<" under budget";
    }
}