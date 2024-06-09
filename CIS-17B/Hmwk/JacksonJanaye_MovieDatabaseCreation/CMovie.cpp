/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>   //I/O Library
#include <cstdlib>    //Random Number Generator, Setting seed, etc....
#include <iomanip>    //Formatting Library
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;  //Libraries compiled under std


#include "CMovie.h"

//deconstructor
CMovie::~CMovie(){
    delete [] movies->mveInfo;//Now the array of Structures
    delete movies;//Now deallocate the final Movie Structure
}

//display data
void CMovie::display(){
    //Loop on the data
    for(int mvees=0;mvees<nMovies;mvees++){
        //output data
        cout<<left<<endl;
        cout<<setw(11)<<"Title:"<<movies->mveInfo[mvees].movName<<endl;
        cout<<setw(11)<<"Director:"<<movies->mveInfo[mvees].dirName<<endl;
        cout<<setw(11)<<"Year:"<<movies->mveInfo[mvees].yrRlsd<<endl;
        cout<<setw(11)<<"Length:"<<movies->mveInfo[mvees].runTime<<endl;
    }
}


void CMovie::readInAll(){
    cout<<endl<<"Reading in all movie names"<<endl<<endl;
    fstream in("data.txt",ios::in|ios::binary);
    if(in){
        in.read(reinterpret_cast<char*>(&movies->mveInfo),sizeof(movies->mveInfo));
    }
    for(int i=0; i<nMovies; ++i){
        cout<<i+1<<". "<<movies->mveInfo[i].movName<<endl;
    }
    in.close();
}

MovieInfo* CMovie::readIn(int record){
    fstream in("data.bin",ios::in|ios::binary);
    cout<<endl<<"Accessing random item in file"<<endl;    
    //Declare and initialize variables
    long cursor=0L;    //Where to place the cursor
    MovieInfo *a=new MovieInfo;//Declare the array to return
    
    //Find the record
    cursor=record*sizeof(MovieInfo);
    
    //Fill the structure
    in.seekg(cursor,ios::beg);
    in.read(reinterpret_cast<char *>(a),sizeof(MovieInfo));
    return a;
}

//set movie name
void CMovie::setName(fstream &in, int mvees){
    getline(in, movies->mveInfo[mvees].movName);
}

//set director
void CMovie::setDir(fstream &in, int mvees){
    int size=81;//Make it Dynamic
    string temp = "";
    movies->mveInfo[mvees].dirName=new char[size];
    getline(in, temp);
    for(int i = 0; i < temp.size(); i++){
        movies->mveInfo[mvees].dirName[i]=temp[i];
    }
    
}

//set year
void CMovie::setYear(fstream &in, int mvees){
    in>>movies->mveInfo[mvees].yrRlsd;
}

//set run time
void CMovie::setRun(fstream &in, int mvees){
    in>>movies->mveInfo[mvees].runTime;
}


//write data to binary file
void CMovie::wrtBin(fstream &out, MovieInfo a){//Gotta frickin indent!!!!!
    out.write(reinterpret_cast<char *>(&a),sizeof(MovieInfo));
}

//constructor
CMovie::CMovie(){
    //Declare the Structure array
    movies=new Movies[nMovies];
    fstream out;
    fstream movN,movD, movY, movT;

    //Output
    cout<<"This program reviews creating and retrieving from binary file"<<endl;
    //open binary file
    out.open("data.bin",ios::out|ios::binary);
    movN.open("name.txt", ios::in);
    movD.open("drctr.txt", ios::in);
    movY.open("year.txt", ios::in);
    movT.open("run.txt", ios::in);
    
    
    
    //Allocate the array dynamically
    movies->mveInfo=new MovieInfo[nMovies];

    //Loop on the data
    for(int mvees=0;mvees<nMovies;mvees++){
        setName(movN, mvees);
        setDir(movD, mvees);
        setYear(movY, mvees);
        setRun(movT, mvees);
        
        //add data to binary file
        wrtBin(out, movies->mveInfo[mvees]);
    }
    movN.close();
    movD.close();
    movY.close();
    movT.close();
    out.close();
}