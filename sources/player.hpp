#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "card.hpp"
using namespace std;

namespace ariel{
    class Player{
        private:
        string name;
        vector<Card> cardsStack;   //the player's stack
        int numOfWonCards = 0;
        int numOfWinnings = 0;
        bool isPlaying = false;
        

        public:
        Player();
        Player(string name);
        int stacksize();    //the amout of cards that left
        int cardesTaken();  //the amount of cards the player has won
        string getName();
        int getNumOfWinnings();
        void increaseNumOfWinnings();
        int getNumOfWonCards();
        void increaseNumOfWonCards();
        void increaseNumOfWonCard();
        bool getIsPlaying();
        void setIsPlaying();
        void addCardToStack(Card c);
        vector<Card> getStack();
    };
}
