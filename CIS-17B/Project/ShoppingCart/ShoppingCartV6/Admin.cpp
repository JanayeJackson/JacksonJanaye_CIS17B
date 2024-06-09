/* 
 * File:   main.cpp
 * Author: Janaye Jackson
 *
 * Created on April 24th, 2024, 6:58 PM
 * Purpose: Create a shopping cart with a user and admin
 */

#include "Admin.h"


Admin::~Admin(){
    delete [] cLog->cat;//deallocate array of structures
    delete cLog;//Now deallocate the final catalog Structure
    delete admins;
}

void Admin::addAdmin(){
    nAd++;
    if(nAd >= 10){
        cout<<"You can only have 10 admins"<<endl;
        menu();
    }
    string user, password;
    string role = "admin";
    char choice;
    bool accept = false;
    profile *a = new profile;
    do{
        cout<<"Please enter new Admin user name and password"<<endl;
        cout<<"Username: ";
        cin>>user;
        cout<<"Password: ";
        cin>>password;
    
        cout<<"Username: "<<user<<" Password: "<<password<<endl;
        cout<<"Is this the correct username and password (y or n)";
        cin>>choice;
        if(choice == 'y'){
            accept = true;
            for(int i = 0; i < user.size(); i++)
                admins[nAd].user[i] = user[i];
            for(int i = 0; i < password.size(); i++)
                admins[nAd].pass[i]=password[i];
            for(int i = 0; i < role.size(); i++)
                admins[nAd].role[i]=role[i];
            
        }
    }while(!accept);
    cout<<"user: "<<admins[nAd].user<<" pass: "<<
            admins[nAd].pass;
    cout<<"\nYou have added an admin"<<endl;
    a->user = admins[nAd].user;
    a->pass = admins[nAd].pass;
    a->role = admins[nAd].role;
    a->size = admins[nAd].size;
    cout<<nAd;
    wrtBin(a);
    menu();
}

void Admin::addItem(){
    //declare variables
    fstream in;
    string input;
    char *name, *image;
    float price;
    int size = 100;
    nItems++;
    name = new char[size];
    image = new char[size];
    catalog *temp = new catalog[nItems];
    temp->cat = new item[nItems];
    //open file
    in.open("Catalog.txt", ios::app);
    
    //get new item information
    cout<<"Input item name: ";
    cin.ignore();
    getline(cin,input);
    cout<<"Input image name: ";
    cin>>image;
    cout<<"Input price: ";
    cin>>price;
    
    //format name
    replace(input.begin(), input.end(), ' ', '-');
    for(int i = 0; i < input.length(); i++){
        name[i] = input[i];
    }
    
    //add to structure
    temp->cat[nItems - 1].name = name;
    temp->cat[nItems - 1].pic = image;
    temp->cat[nItems-1].amount = 0;
    temp->cat[nItems - 1].price = price;
    
    //copy array of structure to temp
    for(int i = 0; i < nItems -1; i++){
        temp->cat[i] = cLog->cat[i];
    }
    cLog = temp;
    
    //output new item to catalog file
    in<<"\n"<<name<<"\t"<<image<<"\t0\t"<<price;
    //output
    cout<<"You have added an item"<<endl;
    in.close();//close file
    menu();//call menu 
    
}
void Admin::deleteAdmin(){
    int choice;
    fstream out;
    profile *a = new profile;
    if(nAd == 0){
        cout<<"You cannot have 0 admins"<<endl;
        menu();
    }
    printAdmin();
    do{
        cout<<"Which Admin would you like to delete? Pick a number";
        cin>>choice;
    }while(choice < 1 || choice > nAd+1);
    
    
    out.open("admin.bin",ios::out|ios::binary);
    
    for(int i = 0; i <= nAd; i++){
        if(choice == i + 1)
            continue;
        a->user = admins[i].user;
        a->pass = admins[i].pass;
        a->role = admins[i].role;
        a->size = admins[i].size;
        cout<<a->user;
        wrtNBin(out, a);
    }
    out.close();
    
    for(int i = 0; i < 10; i++){
        a = readInAdmin(i);
        cout<<a->user;
        if(a->user[i] == '\0'){
            cout<<i<<endl;
            admins[i].user = new char[a->size];
            admins[i].pass=  new char[a->size];
            admins[i].role =  new char[a->size];
            break;
        }    
        admins[i].user = a->user;
        admins[i].pass= a->pass;
        admins[i].role = a->role;
        admins[i].size = a->size;
        nAd = i;
        cout<<nAd<<endl;
    }
    menu();
    
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
    nItems--;
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
        cout<<"1. List of Admins"<<endl;
        cout<<"2. Add Admin"<<endl;
        cout<<"3. Delete Admin"<<endl;
        cout<<"4. Show Catalog"<<endl;
        cout<<"5. Add Item"<<endl;
        cout<<"6. Delete Item"<<endl;
        cout<<"7. Quit"<<endl;
        
        cin>>choice;
        //input validation
        if(choice < 1 || choice > 7){
            valid = false;
            cout<<"Invalid Option please select a valid option"<<endl;
        }
        else
            valid = true;
                    
    }while(!valid);
    
    //call function based on choice
    switch(choice){
        case(1):
            printAdmin();
            menu();
            break;
        case(2):
            addAdmin();
            break;
        case(3):
            deleteAdmin();
            break;
        case(4):
            showCatalog();
            break;
        case(5):
            addItem();
            break;
        case(6):
            deleteItem();
            break;
        default:
            cout<<"Thank you for reviewing the catalog"<<endl;
    }
    
}

profile * Admin::readInAdmin(int record){
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
void Admin::printAdmin(){
    cout<<"The Admins are: "<<endl;
    for(int i = 0; i <= nAd; i++){
        cout<<i+1<<". ";
        cout<<admins[i].user<<endl;
    }
}

void Admin::ReadIn(){
    //declare variables
    fstream in;
    in.open("Catalog.txt", ios::in);//open file
    int i = 0;
    string name, pic;
    int amount;
    float price;
    
    //loop through file
    while(!in.eof()){
        in>>name>>pic>>amount>>price;
        for(int j = 0; j < name.length(); j++)
            cLog->cat[i].name[j] = name[j];
        for(int j = 0; j < pic.length(); j++)
            cLog->cat[i].pic[j] = pic[j];
        cLog->cat[i].amount = amount;
        cLog->cat[i].price = price;
        i++;
    }
    in.close();//close file
}

void Admin::showCatalog(){
    //Loop through to display data
    for(int i = 0; i<nItems; i++){
        cout<<"#"<<i+1<<endl;
        cout<<"Item Name: "<<cLog->cat[i].name<<endl;
        cout<<"price: "<<showpoint<<fixed<<setprecision(2)<<cLog->cat[i].price<<endl;
    }
}

void Admin::wrtBin(profile *a){
    fstream out; 
    out.open("admin.bin",ios::app|ios::binary);
    out.write(reinterpret_cast<char *>(&a->size),sizeof(int));
    out.write(reinterpret_cast<char *>(a->user),a->size*sizeof(int)); 
    out.write(reinterpret_cast<char *>(a->pass),a->size*sizeof(int)); 
    out.write(reinterpret_cast<char *>(a->role),a->size*sizeof(int)); 
    out.close();
}

void Admin::wrtNBin(fstream &out, profile *a){
    out.write(reinterpret_cast<char *>(&a->size),sizeof(int));
    out.write(reinterpret_cast<char *>(a->user),a->size*sizeof(int)); 
    out.write(reinterpret_cast<char *>(a->pass),a->size*sizeof(int)); 
    out.write(reinterpret_cast<char *>(a->role),a->size*sizeof(int)); 
}



Admin::Admin(){
    //declare and initialize variables
    int size = 81;
    int cSize = 100;
    nItems = getSize();
    cLog = new catalog[nItems];
    cLog->cat = new item[nItems];
    profile *a = new profile;
    string temp = "";
    
    //initialize array of items
    for(int i = 0; i < nItems; i++){
        cLog->cat[i].name = new char[cSize];
        cLog->cat[i].pic = new char[cSize];
        cLog->cat[i].amount = 0;
        cLog->cat[i].price = 0.0;
    }
    //initialize array of admins
    admins = new profile[10];
    for(int i = 0; i < 10; i++){
        admins[i].size = size;
        admins[i].user = new char[size];
        admins[i].pass = new char[size];
        admins[i].role = new char[size];
    }
    
    //read in already created admins
    for(int i = 0; i < 10; i++){
        a = readInAdmin(i);
        if(a->user[0] == '\0')
            break;
        admins[i].user = a->user;
        admins[i].pass= a->pass;
        admins[i].role = a->role;
        admins[i].size = a->size;
        nAd = i;
    }
    cout<<"Welcome Admin"<<endl;
    
    //read in catalog from file
    ReadIn();
    menu();//show menu
}