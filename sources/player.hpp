#pragma once
#include <string>
#include <iostream>
using namespace std;

namespace ariel{
    class Player{
        private:
        string name;
        vector<Cards> cardsStack;   //the player's stack
        // vector<Cards> wonCardsStack; //the player's won cards stack
        int numOfWonCards = 0;
        int getNumOfWinnings = 0;
        

        public:
        Player();
        Player(string name);
        int stacksize();    //the amout of cards that left
        int cardesTaken();  //the amount of cards the player has won
        string getName();
        int getNumOfWinnings();
        int getNumOfWonCards();
        void increaseNumOfWonCards();
    };
}
