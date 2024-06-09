/* 
 * File:   Login.cpp
 * Author: Janaye Jackson
 *
 * Created on April 26, 2024, 6:21 PM
 */

#include <cstdlib>
#include "Login.h"

using namespace std;

Login::Login(char *u){
    //declare and initialize variables
    int size = 81;
    char choice;
    profile *a = new profile;
    bool noAdmin = true;
    bool noUser = true;
    bool cPass = false;
    int tries = 0;
    char *p = new char[81];
    
    //read in already created admins
    for(int i = 0; i < 10; i++){
        a = readInAdmin(i);
        if(a->user[0] == '\0')
            break;
        if(match(a->user, u)){
            noAdmin = false;
            break;
        }
    }
    if(!noAdmin){
        do{
                cout<<"Password: ";
                cin>>p;
                if(matchP(a->pass, p)){
                    cPass = true;
                    break;
                }
                else{
                    cout<<"Incorrect password"<<endl;
                    tries++;
                }
            }while(!cPass && tries < 3);
            if(cPass)
                Admin ad;
            if(tries > 3)
                cout<<"Too many failed attempts";
    }
    if(noAdmin){
        for(int i = 0; i < 10; i++){
            a = readInUser(i);
            if(a->user[0] == '\0')
                break;
            if(match(a->user, u)){
                noUser = false;
                break;
            }
        }
        if(!noUser){
            do{
                cout<<"Password: ";
                cin>>p;
                if(matchP(a->pass, p)){
                    cPass = true;
                    break;
                }
                else{
                    cout<<"Incorrect password"<<endl;
                    tries++;
                }
            }while(!cPass && tries < 3);
            if(cPass)
                User shop(u);
            if(tries > 3)
                cout<<"Too many failed attempts";
        }
    }
    if(noAdmin && noUser){
        cout<<"Could not fine User"<<endl;
        cout<<"Would you like to create one: (y or n)";
        cin>>choice;
        if(choice == 'y' || choice == 'Y'){
            cin>>p;
            addUser(u, p);
        }
    }
    delete a;
}

void Login::addUser(char *u, char *p){
    fstream out; 
    profile *a = new profile;
    string temp = "admin";
    a->user = u;
    a->pass = p;
    a->role = new char[81];
    a->size = 81;
    
    for(int i = 0; i < temp.length(); i++){
        a->role[i] = temp[i];
    }
    
    out.open("User.bin",ios::app|ios::binary);
    out.write(reinterpret_cast<char *>(&a->size),sizeof(int));
    out.write(reinterpret_cast<char *>(a->user),a->size*sizeof(int)); 
    out.write(reinterpret_cast<char *>(a->pass),a->size*sizeof(int)); 
    out.write(reinterpret_cast<char *>(a->role),a->size*sizeof(int)); 
    out.close();
}

profile *Login::readInAdmin(int record){
    fstream in("admin.bin",ios::in|ios::binary);
    int count = 0;
    long cursor = 0L;
    //Declare and initialize variables
    profile *a = new profile; //Declare the array to return
    a->size = 81;
    a->user = new char [a->size];
    a->pass = new char [a->size];
    a->role = new char [a->size];
    if(in){
    while(++count<=record){
        in.seekg(cursor,ios::beg);
        in.read(reinterpret_cast<char *>(&a->size),sizeof(int));
        cursor+=(sizeof(int)+a->size*sizeof(int)+a->size*sizeof(int)+a->size*sizeof(int));
    }
    
    in.seekg(cursor, ios::beg);
    in.read(reinterpret_cast<char *>(&a->size),sizeof(int));
    in.read(reinterpret_cast<char *>(a->user),a->size*sizeof(int));
    in.read(reinterpret_cast<char *>(a->pass),a->size*sizeof(int));
    in.read(reinterpret_cast<char *>(a->role),a->size*sizeof(int));
    }
    in.close();
    
    return a;   
}

profile *Login::readInUser(int record){
    fstream in("User.bin",ios::in|ios::binary);
    int count = 0;
    long cursor = 0L;
    //Declare and initialize variables
    profile *a = new profile; //Declare the array to return
    a->size = 81;
    a->user = new char [a->size];
    a->pass = new char [a->size];
    a->role = new char [a->size];
    if(in){
    while(++count<=record){
        in.seekg(cursor,ios::beg);
        in.read(reinterpret_cast<char *>(&a->size),sizeof(int));
        cursor+=(sizeof(int)+a->size*sizeof(int)+a->size*sizeof(int)+a->size*sizeof(int));
    }
    
    in.seekg(cursor, ios::beg);
    in.read(reinterpret_cast<char *>(&a->size),sizeof(int));
    in.read(reinterpret_cast<char *>(a->user),a->size*sizeof(int));
    in.read(reinterpret_cast<char *>(a->pass),a->size*sizeof(int));
    in.read(reinterpret_cast<char *>(a->role),a->size*sizeof(int));
    }
    in.close();
    
    return a;   
}

bool Login::match(char * a, char *b)
{
    int match = true;
    char temp1, temp2;
    for(int i = 0; i < 81; i++){
        if(a[i] == '\0' || b[i] == '\0'){
            if(a[i] == '\0' && b[i] != '\0')
                match = false;
            else if(a[i] != '\0' && b[i] == '\0')
                match = false;
            break;
        }
            
        temp1 = toupper(a[i]);
        temp2 = toupper(b[i]);
        if(temp1 != temp2){
            match = false;
            break;
        }
            
    }
    
    return match; 
}

bool Login::matchP(char * a, char *b)
{
    int match = true;
    for(int i = 0; i < 81; i++){
        if(a[i] == '\0' || b[i] == '\0'){
            if(a[i] == '\0' && b[i] != '\0')
                match = false;
            else if(a[i] != '\0' && b[i] == '\0')
                match = false;
            break;
        }
        if(a[i] != b[i]){
            match = false;
            break;
        }    
    }
    return match; 
}

