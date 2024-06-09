/* 
 * File:   AdminStructure.h
 * Author: Janaye Jackson
 *
 * Created on April 11th, 2024, 11:30 AM
 */

#ifndef ADMINSTRUCTURE_H
#define ADMINSTRUCTURE_H

#include <string>
#include "profile.h"

struct admins {
    profile *admin;
    string role = "admin";
};



#endif /* ADMINSTRUCTURE_H */

