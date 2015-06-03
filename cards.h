#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string>

using namespace std;

class cards
{

     private:
    //varibles that the setter functions will use
    string face;
    string suit;
    int value;
    int value2;
    
    
    
    public:
    //constructors
    cards(); //default constructor
    cards(int i, int k); //user Defined Constructor
    cards(const cards &other); //copy constructor
    //cards& operator=(const cards &other);    operation overload dont use. unless we have to
    
    //seters
    void setFaceValue(int i);
    void setSuitValue(int k);
    void setValue(int i);
    
    
    //getters
    void printCard();
    void printCardNoEndl();
    int getValue1();
    int getValue2();


    
    



    
    
};

#endif