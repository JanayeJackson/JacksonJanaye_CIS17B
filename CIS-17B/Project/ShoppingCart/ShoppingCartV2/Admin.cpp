/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 *
 * Created on April 10th, 2024, 6:13 PM
 * Purpose: Create a shopping cart with a user and admin
 */

#include "Admin.h"


Admin::~Admin(){
    
}
void Admin::addAdmin(){
    cout<<"You have added an admin"<<endl;
    menu();
    
    
}

void Admin::addItem(){
    cout<<"You have added an item"<<endl;
    menu();
    
}

void Admin::deleteItem(){
    cout<<"You have deleted an item"<<endl;
    menu();
    
}

int Admin:: getSize(){
    int j =0;
    fstream in;
    string temp;
    in.open("Catalog.txt", ios::in);
    while(!in.eof()){
        getline(in, temp);
        j++;
    }
    return j-1;
}

void Admin::menu(){
    bool valid = false;
    int choice;
    do{
        cout<<"What would you like to do with the catalog"<<endl;
        cout<<"1. Add Admin"<<endl;
        cout<<"2. Add Item"<<endl;
        cout<<"3. Delete Item"<<endl;
        cout<<"4. Quit"<<endl;
        cin>>choice;
        if(choice < 1 || choice > 4){
            valid = false;
            cout<<"Invalid Option please select a valid option"<<endl;
        }
        else
            valid = true;
                    
    }while(!valid);
    
    switch(choice){
        case(1):
            addAdmin();
            break;
        case(2):
            addItem();
            break;
        case(3):
            deleteItem();
            break;
        default:
            cout<<"Thank you for reviewing the catalog"<<endl;
    }
    
}

void Admin::ReadIn(){
    fstream in;
    in.open("Catalog.txt", ios::in);
    int i = 0;
    
    while(!in.eof()){
        in>>cLog->cat[i].name>>cLog->cat[i].pic>>cLog->cat[i].amount
                >>cLog->cat[i].price;
        i++;
    }
    in.close();
    //nItems = i - 1;
}

void Admin::wrtBin(){
    
}

void Admin::showCatalog(){
    //Loop through to display data
    for(int i = 0; i<nItems; i++){
        cout<<"#"<<i+1<<endl;
        cout<<"Item Name: "<<cLog->cat[i].name<<endl;
        cout<<"price: "<<showpoint<<fixed<<setprecision(2)<<cLog->cat[i].price<<endl;
    }
}


Admin::Admin(){
    nItems = getSize();
    cLog = new catalog[nItems];
    cLog->cat = new item[nItems];
    ReadIn();
    showCatalog();
    menu();
}


