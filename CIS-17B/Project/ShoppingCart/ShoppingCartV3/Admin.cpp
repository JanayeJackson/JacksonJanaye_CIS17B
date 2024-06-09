/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 *
 * Created on April 11th, 2024, 11:30 AM
 * Purpose: Create a shopping cart with a user and admin
 */

#include "Admin.h"


Admin::~Admin(){
    delete [] cLog->cat;//deallocate array of structures
    delete cLog;//Now deallocate the final catalog Structure
    
}
void Admin::addAdmin(){
    cout<<"You have added an admin"<<endl;
    menu();
    
    
}

void Admin::addItem(){
    //declare variables
    fstream in;
    string name, image;
    float price;
    //open file
    in.open("Catalog.txt", ios::app);
    
    //get new item information
    cout<<"Input item name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Input image name: ";
    cin>>image;
    cout<<"Input price: ";
    cin>>price;
    
    //format name
    replace(name.begin(), name.end(), ' ', '-');

    //output new item to catalog file
    in<<"\n"<<name<<"\t"<<image<<"\t0\t"<<price;
    //output
    cout<<"You have added an item"<<endl;
    in.close();//close file
    menu();//call menu 
    
}

void Admin::deleteItem(){
    //deckare variables
    fstream in, out;
    int num;
    string item;
    
    //open files
    in.open("Catalog.txt", ios::in);
    out.open("temp.txt", ios::out);
    
    //Get item to delete
    cout<<"What item # would you like to delete:";
    cin>>num;
    
    //append file
    for(int i = 0; i < nItems; i++){
        getline(in, item);
        if(i != num - 1){
            out<<item<<endl;
        }
    }
    
    //close files
    in.close();
    out.close();
    
    //replace old file withe new file
    remove("Catalog.txt");
    rename("temp.txt", "Catalog.txt");
    
    cout<<"You have deleted an item"<<endl;
    menu(); //call menu
    
}

int Admin:: getSize(){
    //declare variables
    int j =0;
    fstream in;
    string temp;
    //open file
    in.open("Catalog.txt", ios::in);
    //loop through file
    while(!in.eof()){
        getline(in, temp);
        j++;
    }
    //cout size of file
    return j;
}

void Admin::menu(){
    //declare variables
    bool valid = false;
    int choice;
    
    //display menu
    do{
        cout<<"What would you like to do with the catalog"<<endl;
        cout<<"1. Add Admin"<<endl;
        cout<<"2. Add Item"<<endl;
        cout<<"3. Delete Item"<<endl;
        cout<<"4. Quit"<<endl;
        cin>>choice;
        //input validation
        if(choice < 1 || choice > 4){
            valid = false;
            cout<<"Invalid Option please select a valid option"<<endl;
        }
        else
            valid = true;
                    
    }while(!valid);
    
    //call function based on choice
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
    //declare variables
    fstream in;
    in.open("Catalog.txt", ios::in);//open file
    int i = 0;
    
    //loop through file
    while(!in.eof()){
        in>>cLog->cat[i].name>>cLog->cat[i].pic>>cLog->cat[i].amount
                >>cLog->cat[i].price;
        i++;
    }
    in.close();//close file
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
    //declare and initialize variables
    nItems = getSize();
    cLog = new catalog[nItems];
    cLog->cat = new item[nItems];
    
    //read in catalog from file
    ReadIn();
    showCatalog();//show catalog
    menu();//show menu
}


