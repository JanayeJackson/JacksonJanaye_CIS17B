/* 
 * File:   Admin.h
 * Author: Janaye Jackson
 *
 * Created on April 11th 2024, 11:30 AM
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
#include "AdminStructure.h"

class Admin{
private:
    catalog *cLog;
    admins *aUser;
public:
    Admin();
    ~Admin();
    void addAdmin();
    void addItem();
    void deleteItem();
    int getSize();
    void menu();
    void ReadIn();
    void wrtBin();
    void showItems();
    void showCatalog(); 
    int nItems = 0;
};


#endif /* ADMIN_H */

