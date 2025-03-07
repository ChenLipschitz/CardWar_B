#pragma once
#include <iostream>
#include "player.hpp"
#include "card.hpp"

namespace ariel{
    class Game{
        private:
        Player &player1;
        Player &player2;
        string winnersName;
        int numOfDraws = 0;
        vector<string> gameStatus;
        int numOfRounds = 0;
        void handOutCards();
        void shuffleCards(vector<Card> &deck);

        public:
        Game(Player& player1, Player& player2);    
        void playTurn();
        void printLastTurn();
        void printWiner();
        void printLog();
        void printStats();
        void playAll();
        int getNumOfDraws();
        int getNumOfRounds();
        void increaseNumOfRounds();
        int dualTurn(Card card1, Card card2);
    };
}