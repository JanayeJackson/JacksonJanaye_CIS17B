/* 
 * File:   Dice.h
 * Author: Janaye Jackson
 * Created on April 28th, 2024, 7:40 PM
 * Purpose:  To create and display faces of a dice
 */

#ifndef DICE_H
#define DICE_H

    #include <string>
    using namespace std;

    class Dice{
        private:
            static const int MAXFACE=6;
            static const int MINFACE=0;
            int    number;
            int    faceVal;
            string name;
            string picture;
            void   setFace();
            void   setName();
            void   setPict();
        public:
            Dice(int);
            int    getNumr(){return number;}
            int    getFace(){return faceVal;}
            string getName(){return name;}
            string getPict(){return picture;}
            string toString();
    };

#endif /* DICE_H */