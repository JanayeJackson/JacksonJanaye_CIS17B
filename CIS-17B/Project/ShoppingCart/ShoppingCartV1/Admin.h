/* 
 * File:   Admin.h
 * Author: Janaye Jackson
 *
 * Created on April 8th 2024, 6:51 PM
 */

#ifndef ADMIN_H
#define ADMIN_H

#include "AdminStructure.h"

class Admin{
private:
    item *catalog;
    admins *aUser;
public:
    Admin();
    ~Admin();
    void addAdmin();
    void addItem();
    void deleteItem();
    void menu();
    void ReadIn();
    void wrtBin();
    void showCatalog();    
};



#endif /* ADMIN_H */

