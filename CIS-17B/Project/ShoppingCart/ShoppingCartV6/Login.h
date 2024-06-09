
/* 
 * File:   Login.h
 * Author: nayen
 *
 * Created on April 27, 2024, 6:54 PM
 */


#ifndef LOGIN_H
#define LOGIN_H

#include "profile.h"
#include "Admin.h"
#include "User.h"

class Login{
public:
    Login(char *);
    void addUser(char *, char*);
    profile *readInAdmin(int);
    profile *readInUser(int);
    bool match(char *, char *);
    bool matchP(char *, char *);
};



#endif /* LOGIN_H */

