/* 
 * File:   Dice.cpp
 * Author: Janaye Jackson
 * Created on April 28th, 2024, 7:40 PM
 * Purpose:  To create and display faces of a dice
 */

#include "Dice.h"
#include <sstream>
using namespace std;

Dice::Dice(int number){
    if(number>=MINFACE&&number<MAXFACE){
        this->number=number;
        setFace();
        setName();
        setPict();
    }else{
        this->number=-1;
        this->faceVal=-1;
        this->name="none";
        this->picture="none";
    }
}

void Dice::setFace(){
    int num=this->number%6+1;
    this->faceVal=num;
}
            
void Dice::setName(){
    switch(this->number%6){
        case 0:  this->name="One";  break;
        case 1:  this->name="Two";  break;
        case 2:  this->name="Three";break;
        case 3:  this->name="Four"; break;
        case 4:  this->name="Five"; break;
        case 5:  this->name="Six";  break;
        default: this->name="Bad Value";
    }
}
            
void Dice::setPict(){
    this->picture="cards/"+this->name+".png";
}
   
string Dice::toString(){
    ostringstream cnvNum,cnvFace;
    cnvNum  << this->number;
    cnvFace << this->faceVal;
    string str="\n";
    str+=("<img src="+this->picture+" />");
    str+=("\nNumber = "+cnvNum.str());
    str+=("\nName = "+this->name);
    str+=("\nFace Value = "+cnvFace.str());
    str+=("\n \n");
    return str;
}