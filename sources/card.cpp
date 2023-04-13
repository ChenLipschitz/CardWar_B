#include "card.hpp"
#include "string"
using namespace ariel;

Card::Card(int value_, string shape_){
    this->value = value_;
    this->shape = shape_;
}

int Card::getValue(){
    return this->value;
}

string Card::getShape(){
    return this->shape;
}

//compares between two cards
//if the cuurent card is greater return 1
//if less return -1
//if equal 0
int Card::compareTo(Card other){
    if (this->value == 1 && other.getValue() != 2 && other.getValue() != 1){    //Ace agaist 3-13-> Ace wins
        return 1;
    }
    if (this->value != 2 && this->value != 1 && other.getValue() == 1){     //Ace against 3-13-> Ace wins
        return -1;
    }
    if(this->value > other.getValue()){    
        return 1;
    }
    if (this->value < other.getValue()){
        return -1;
    }
    return 0;
}

string Card::toString(){
    string valueN = "";
    if (this->value == 1)
        valueN = "Ace";
    if (this->value == 11)
        valueN = "Jack";
    if (this->value == 12)
        valueN = "Queen";
    if (this->value == 13)
        valueN = "King";
    return valueN+" "+"of"+" "+this->shape;
}