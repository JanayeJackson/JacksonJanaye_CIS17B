/* 
 * File:   User.cpp
 * Author: Janaye Jackson
 *
 * Created on April 26th, 2024, 5:49 PM
 */

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "User.h"

using namespace std;

User::~User(){
    delete [] cLog->cat;//deallocate array of structures
    delete cLog;//Now deallocate the final catalog Structure
    //delete admins;
}

void User::addToCart(){
    int choice;
    bool valid = false;
    int amount;
    if(uLog[0].name[0] == '\0'){
        showCatalog();
        cout<<"What item would you like to add to your cart"<<endl;
        cin>>choice;
        uLog[nCart].name = cLog->cat[choice - 1].name;
        uLog[nCart].pic = cLog->cat[choice -1].pic;
        uLog[nCart].amount += 1;
        uLog[nCart].price = cLog->cat[choice - 1].price;
        nCart++;
    }
    else{
        do{
            cout<<"Would you like to add a new item or increase amount of another item"<<endl;
            cout<<"1. add"<<endl;
            cout<<"2. increase"<<endl;
            cin>>choice;
            if(choice == 1 || choice == 2)
                valid = true;
        }while(!valid);
        if(choice == 1){
            showCatalog();
            cout<<"What item would you like to add to your cart"<<endl;
            cin>>choice;
            uLog[nCart].name = cLog->cat[choice - 1].name;
            uLog[nCart].pic = cLog->cat[choice -1].pic;
            uLog[nCart].amount += 1;
            uLog[nCart].price = cLog->cat[choice - 1].price;
            nCart++;
        }
        else{
            showCart();
            cout<<"What item would you like to increase"<<endl;
            cin>>choice;
            cout<<"How much do you want to add"<<endl;
            cin>>amount;
            uLog[choice - 1].amount += amount;
        }
    }
    menu();
}
void User::deleteFromCart(){
    int choice;
    bool valid = false;
    int amount;
    if(uLog[0].name[0] == '\0'){
        cout<<"You have nothing in your cart"<<endl;
    }
    else{
        do{
            cout<<"Would you like to delete an item or decrease amount of another item"<<endl;
            cout<<"1. delete"<<endl;
            cout<<"2. decrease"<<endl;
            cin>>choice;
            if(choice == 1 || choice == 2)
                valid = true;
        }while(!valid);
        if(choice = 1){
            showCart();
            cout<<"What item would you like to delete from your cart"<<endl;
            cin>>choice;
            for(int i = 0, j = 0; i < nItems && j < nItems; i++, j++){
                if(uLog[i].name[0] == '\0')
                    break;
                if(i == choice - 1)
                    j++;
                uLog[i].name = uLog[j].name;
                uLog[i].pic = uLog[j].pic;
                uLog[i].price = uLog[j].price;
                uLog[i].amount = uLog[j].amount;
                
            }
        }
        else{
            showCart();
            cout<<"What item would you like to decrease"<<endl;
            cin>>choice;
            cout<<"How much do you want to decrease by"<<endl;
            cin>>amount;
            uLog[choice - 1].amount -= amount;
            if(uLog[choice - 1].amount <= 0){
                for(int i = 0, j = 0; i < nItems && j < nItems; i++, j++){
                if(uLog[i].name[0] == '\0')
                    break;
                if(i == choice - 1)
                    j++;
                uLog[i].name = uLog[j].name;
                uLog[i].pic = uLog[j].pic;
                uLog[i].price = uLog[j].price;
                uLog[i].amount = uLog[j].amount;
                
            }
                
            }
        }
    }
    menu();
}

void User::done(){
    fstream out;
    string filename = user; 
    filename+= ".bin";
    item *a = new item;
    a->size = 100;
    a->name = new char[a->size];
    a->pic = new char[a->size];
    int aPrice;
    out.open(filename, ios::out|ios::binary);
    for(int i = 0; i < nCart; i++){
        a->name = uLog[i].name;
        a->pic = uLog[i].pic;
        a->amount = uLog[i].amount;
        aPrice = int(uLog[i].price * 100);
        out.write(reinterpret_cast<char *>(&a->size), sizeof(int));
        out.write(reinterpret_cast<char *>(a->name),a->size*sizeof(int)); 
        out.write(reinterpret_cast<char *>(a->pic),a->size*sizeof(int));
        out.write(reinterpret_cast<char *>(&a->amount),sizeof(int)); 
        out.write(reinterpret_cast<char *>(&aPrice),sizeof(int));
    }
    out.close();
    
}

int User::getSize(){
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
    in.close();
    return j;
}

void User::menu(){
    int choice;
    bool valid = false;
    do{
        cout<<"Menu Options"<<endl;
        cout<<"1. Show Catalog"<<endl;
        cout<<"2. Add Item To Your Cart"<<endl;
        cout<<"3. Delete Item From Your Cart"<<endl;
        cout<<"4. Show Cart"<<endl;
        cout<<"5. Exit"<<endl;
        cin>>choice;
        if(choice > 0 && choice < 6)
            valid = true;
    }while(!valid);
    
    switch(choice){
        case(1):
            showCatalog();
            menu();
            break;
        case(2):
            addToCart();
            break;
        case(3):
            deleteFromCart();
            break;
        case(4):
            showCart();
            menu();
            break;
        default:
            done();
    }
    
}

void User::ReadIn(){
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

item* User::ReadInCart(int record){
    //declare variables
    fstream in;
    int aPrice;
    string filename = user;
    filename+=".bin";
    item *a = new item;
    a->size = 100;
    a->name = new char[a->size];
    a->pic = new char[a->size];
    a->amount = 0;
    aPrice = 0;
    in.open(filename, ios::in|ios::binary);//open file
    
    int count = 0;
    long cursor = 0L;
    //Declare and initialize variables
    if(in){
        while(++count<=record){
            in.seekg(cursor,ios::beg);
            in.read(reinterpret_cast<char *>(&a->size),sizeof(int));
            cursor+=(sizeof(int)+a->size*sizeof(int)+a->size*sizeof(int)+sizeof(int)+sizeof(int));
        }
    
        in.seekg(cursor, ios::beg);
        in.read(reinterpret_cast<char *>(&a->size),sizeof(int));
        in.read(reinterpret_cast<char *>(a->name),a->size*sizeof(int));
        in.read(reinterpret_cast<char *>(a->pic),a->size*sizeof(int));
        in.read(reinterpret_cast<char *>(&a->amount),sizeof(int));
        in.read(reinterpret_cast<char *>(&aPrice),sizeof(int));
        a->price = aPrice/100.00;
    }
    in.close();//close file
    return a;
}
void User::showCart(){
    int i = 0;
    float tPrice = 0;
    if(uLog[0].name[i] == '\0')
        cout<<"Cart is empty"<<endl;
    else{
        cout<<"Cart: "<<endl;
        while(uLog[i].name[0] != '\0'){
            cout<<"#"<<i+1<<endl;
            cout<<"Item Name: "<<uLog[i].name<<endl;
            cout<<"Amount: "<<uLog[i].amount<<endl;
            cout<<"price: "<<showpoint<<fixed<<setprecision(2)<<uLog[i].price<<endl;
            tPrice += uLog[i].price * uLog[i].amount;
            i++;
        }
        cout<<"\nTotal: "<<showpoint<<fixed<<setprecision(2)<<tPrice<<endl;
    }
}

void User::showCatalog(){
    //Loop through to display data
    cout<<"LEGO CATALOG"<<endl;
    for(int i = 0; i<nItems; i++){
        cout<<"#"<<i+1<<endl;
        cout<<"Item Name: "<<cLog->cat[i].name<<endl;
        cout<<"price: "<<showpoint<<fixed<<setprecision(2)<<cLog->cat[i].price<<endl;
    }
}

User::User(char *u){
    //declare and initialize variables
    user = u;
    nItems = getSize();
    cout<<nItems;
    cLog = new catalog[nItems];
    cLog->cat = new item[nItems];
    uLog = new item[nItems];
    item *a = new item;
    
    for(int i = 0; i<nItems;i++){
       cLog->cat[i].size = 100;
       cLog->cat[i].name =  new char[cLog->cat[i].size];
       cLog->cat[i].pic =  new char[cLog->cat[i].size];
    }
    for(int i = 0; i < nItems; i++){
        uLog[i].size = 100;
        uLog[i].name = new char[uLog[i].size];
        uLog[i].pic= new char[uLog[i].size];
        uLog[i].price = 0.0;
        uLog[i].amount=0;
    }
    
    for(int i = 0; i < nItems; i++){
        a = ReadInCart(i);
        if(a->name[0] == '\0')
            break;
        uLog[i].size = a->size;
        uLog[i].name = a->name;
        uLog[i].pic= a->pic;
        uLog[i].price = a->price;
        uLog[i].amount = a->amount;
        nCart = i + 1;
    }
    cout<<"LEGO CATALOG"<<endl;
    
    //read in catalog from file
    ReadIn();
    showCatalog();
    menu();
}
    
