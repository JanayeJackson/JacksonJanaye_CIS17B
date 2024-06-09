/* 
 * File:   Admin.h
 * Author: Janaye Jackson
 *
 * Created on April 24th, 2024, 6:58 PM
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>   //I/O Library
#include <iomanip>    //Formatting Library
#include <string>     //String Library
#include <fstream>    //File Library
#include <algorithm>
using namespace std;

#include "CatStruct.h"
#include "profile.h"

class Admin{
private:
    catalog *cLog;
    profile *admins;
public:
    Admin();
    ~Admin();
    void addAdmin();
    void addItem();
    void deleteAdmin();
    void deleteItem();
    int getSize();
    void menu();
    void printAdmin();
    void ReadIn();
    profile * readInAdmin(int);
    void showCatalog();
    void wrtBin(profile *a);
    void wrtNBin(fstream &, profile *a);
    int nItems = 0;
    int nAd = 0;
};


#endif /* ADMIN_H */

