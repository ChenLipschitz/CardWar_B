#include "card.hpp"
#include "string"
using namespace std;
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
// int Card::compareTo(Card other){
//     if (this->value == 1 && other.getValue() != 2 && other.getValue() != 1){    //Ace agaist 3-13-> Ace wins
//         return 1;
//     }
//     if (this->value != 2 && this->value != 1 && other.getValue() == 1){     //Ace against 3-13-> Ace wins
//         return -1;
//     }
//     if(this->value > other.getValue()){    
//         return 1;
//     }
//     if (this->value < other.getValue()){
//         return -1;
//     }
//     if (this->value == other.getValue()){
//         return 0;
//     }
//     else{
//         throw std::runtime_error("ERROR- cannot compare cards");
//     }
// }

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
    else{
        valueN = to_string(this->value);
    }
    return valueN+" "+"of"+" "+this->shape;
}



// int Game::getRoundWinner(Card card1, Card card2) {
//   if (card1.getRank() == card2.getRank()) {
//     return 0; // tie
//   } else if (card1.getRank() == 1 && card2.getRank() == 2) {
//     return 2; // player 2 wins
//   } else if (card2.getRank() == 1 && card1.getRank() == 2) {
//     return 1; // player 1 wins
//   } else if (((card1.getRank() > card2.getRank()) && card2.getRank() != 1) ||
//              (card1.getRank() == 1 && card2.getRank() != 2)) {
//     return 1; // player 1 wins
//   } else if (((card2.getRank() > card1.getRank()) && card1.getRank() != 1) ||
//              (card2.getRank() == 1 && card1.getRank() != 2)) {
//     return 2; // player 2 wins
//   } else {
//     throw "not good";
//   }