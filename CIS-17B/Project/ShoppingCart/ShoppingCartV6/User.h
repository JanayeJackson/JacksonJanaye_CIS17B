/* 
 * File:   User.h
 * Author: nayen
 *
 * Created on April 27, 2024, 5:52 PM
 */

#ifndef USER_H
#define USER_H

#include "profile.h"
#include "CatStruct.h"

class User{
private:
    catalog *cLog;
    item *uLog;
    string user;
    int nCart = 0;
public:
    User(char *);
    ~User();
    void addToCart();
    void deleteFromCart();
    void done();
    int getSize();
    void menu();
    void ReadIn();
    item * ReadInCart(int);
    void showCart();
    void showCatalog();
    int nItems = 0;
};


#endif /* USER_H */

