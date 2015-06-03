
#include <iostream>
#include "cards.h"
#include <string>

using namespace std;

//default constructor
cards::cards()
{}

//user defined constructor
cards::cards(int i, int k)
{
    setFaceValue(i);
    setSuitValue(k);
    setValue(i);


}

//copy constructor
cards::cards(const cards& other ): suit(other.suit), face(other.face), value(other.value), value2(other.value2)
{}



//get value 1
int cards::getValue1()
{
    return value;
}


//gets value 2
int cards::getValue2()
{
    return value2;
}



//displayCard
void cards::printCard()
{
    cout << face + " of " + suit << endl;
    
}

//Overloaded displayCard for displayRemaining function
void cards::printCardNoEndl()
{
    cout << face + "\tof " + suit;
}


//numerical card value
void cards::setValue(int i)
{
       switch(i)
    {
        case 0:
            value = 1;
            value2 = 11;
        break;
        
        case 1:
            value = 2;
            value2 = 2;
        break;
        
        case 2:
            value = 3;
            value2 = 3;
        break;
        
        case 3:
            value = 4;
            value2 = 4;
        break;
        
        case 4:
            value = 5;
            value2 = 5;
        break;
        
        case 5:
            value = 6;
            value2 = 6;
        break;
        
        case 6:
            value = 7;
            value2 = 7;
        break;
        
        case 7:
            value = 8;
            value2 = 8;
        break;
        
        case 8:
            value = 9;
            value2 = 9;
        break;
        
        case 9:
            value = 10;
            value2 = 10;
        break;
        
        case 10:
            value = 10;
            value2 = 10;
        break;
        
        case 11:
            value = 10;
            value2 = 10;
        break;
        
        case 12:
            value = 10;
            value2 = 10;
        break;
        
        default:
        break;
    }
    
    
}

 
void cards::setSuitValue(int k)
{
    switch(k)
    {
        case 0:
            suit = "Spades";
        break;
        
        case 1:
            suit = "Clubs";
        break;
        
        case 2:
            suit = "Diamonds";
        break;
        
        case 3:
            suit = "Hearts";
        break;
        
        default:
        break;
    }
    
    
}

void cards::setFaceValue(int i)
{
    switch(i)
    {
        case 0:
            face = "Ace";
        break;
        
        case 1:
            face = "2";
        break;
        
        case 2:
            face = "3";
        break;
        
        case 3:
            face = "4";
        break;
        
        case 4:
            face = "5";
        break;
        
        case 5:
            face = "6";
        break;
        
        case 6:
            face = "7";
        break;
        
        case 7:
            face = "8";
        break;
        
        case 8:
            face = "9";
        break;
        
        case 9:
            face = "10";
        break;
        
        case 10:
            face = "Jack";
        break;
        
        case 11:
            face = "Queen";
        break;
        
        case 12:
            face = "King";
        break;
        

        default:
        break;
    }
    
    
}