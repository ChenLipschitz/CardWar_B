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