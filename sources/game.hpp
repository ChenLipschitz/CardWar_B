#pragma once
#include <iostream>
#include "player.hpp"

namespace ariel{
    class Game{
        private:
        Player player1;
        Player player2;
        string winnersName;
        int numOfDraws;
        vector<string> gameStatus;
        int numOfRounds = 0;
        void handOutCards();

        public:
        Game(Player player1, Player player2);    
        void playTurn();
        void printLastTurn();
        void printWiner();
        void printLog();
        void printStats();
        void playAll();
        int getNumOfDraws();
        int getNumOfRounds();
        void increaseNumOfRounds();
    };
}