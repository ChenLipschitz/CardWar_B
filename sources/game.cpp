
#include "player.hpp"
#include "game.hpp"
#include "card.hpp"
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <string>
#include <random>
#include <algorithm>

using namespace std;
using namespace ariel;

Game::Game(Player &player1_, Player &player2_): player1(player1_), player2(player2_){
    //if (player1_.getIsPlaying() || player2_.getIsPlaying){
      //  throw ("A player can play only one game");
    //}
    
    player1.setIsPlaying();
    player2.setIsPlaying();
    handOutCards();
}

void Game::handOutCards(){
    string type1 = "Spades";
    string type2 = "Hearts";
    string type3 = "Diamonds";
    string type4 = "Clubs";

    vector<Card> deck;
    for (int i=1; i<=13; i++){
        deck.push_back(Card(i, type1));
        deck.push_back(Card(i, type2));
        deck.push_back(Card(i, type3));
        deck.push_back(Card(i, type4));
    }

    ///check if the deck was created succssesfuly///
    if (deck.size() != 52){
        throw std::runtime_error("ERROR- Couldn't create the deck");
    }
    
    shuffleCards(deck);
    ///hand out the cards to the players///
    for(unsigned long int i=0; i<26 ;i++){
        
        player1.addCardToStack(deck[i]);
       
    }
    for(unsigned long int i=26; i<52 ;i++){
        player2.addCardToStack(deck[i]);

    }
    // for (int i=1; i<=52; i++){
    //     Card tempCard = deck.back();
    //     deck.pop();
    //     if (i%2 == 1){
    //         player1.cardsStack.push(tempCard);
    //     }
    //     else{
    //         player2.cardsStack.push(tempCard);
    //     }
    // }
}

///used....
void Game::shuffleCards(vector<Card> &deck){
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

void Game::playTurn(){

    ///preliminary checks///
    if (numOfRounds>26){
        throw std::runtime_error("ERROR- Game over");
    }
    if (&player1 == &player2){
        throw std::invalid_argument("ERROR- A player cannot play against himself");
    }
    if (player1.stacksize() == 0 || player2.stacksize() == 0){
        throw std::runtime_error("ERROR- Game was over");
    }

    int result = player1.getStack().back().compareTo(player2.getStack().back());
    string state = player1.getName()+" played "+ player1.getStack().back().toString() +" "+
                player2.getName()+" played "+player2.getStack().back().toString();
    player1.getStack().pop_back();
    player2.getStack().pop_back();
    cout<<player1.getName()<<endl;
    
    ///player1 wins///
    if (result == 1){
        player1.increaseNumOfWonCards();
        player1.increaseNumOfWinnings();
        increaseNumOfRounds();
        gameStatus.push_back(state+". "+player1.getName()+" wins.");
        return;
    }
    ///player2 wins///
    else if (result == -1){
        player2.increaseNumOfWonCards();
        player2.increaseNumOfWinnings();
        increaseNumOfRounds();
        gameStatus.push_back(state+". "+player2.getName()+" wins.");
        return;
    }
    ///Tie///
    else{
        int numOfTies = 0;

        ///start loop///
        while(result == 0){
            state = state + ". Draw. ";
            numOfTies++;
            if (numOfTies > 1){
                player1.getStack().pop_back();
                player2.getStack().pop_back();
            }
            ///incase one of the decks got empty during the draw///
            if (player1.stacksize() == 0 || player2.stacksize() == 0){
                for (int i=0; i<numOfTies; i++){
                    player1.increaseNumOfWonCard();
                    player2.increaseNumOfWonCard();
                    increaseNumOfRounds();
                }
                return;
            }
            result = player1.getStack().back().compareTo(player2.getStack().back());
            state = state + player1.getName()+" played "+ player1.getStack().back().toString() +" "+
                player2.getName()+" played "+player2.getStack().back().toString();
        }
        ///end of loop///

        numOfDraws = numOfDraws + numOfTies;
        ///player1 won the draw///
        if (result == 1){
            for(int i=1; i<=numOfTies; i++){
                player1.increaseNumOfWonCards();
                increaseNumOfRounds();
                return;
            }
            gameStatus.push_back(state+". "+player1.getName()+" wins.");
            player1.increaseNumOfWinnings();
        }

        ///player2 won the draw///
        else{
            for(int i=1; i<=numOfTies; i++){
                player2.increaseNumOfWonCards();
                increaseNumOfRounds();
                return;
            }
            gameStatus.push_back(state+". "+player2.getName()+" wins.");
            player2.increaseNumOfWinnings();
        }
    }
}


void Game::playAll(){
    while(player1.getStack().size() > 0 && player2.getStack().size() > 0){
        playTurn();
    }
}

int Game::getNumOfRounds(){
    return this->numOfRounds;
}

void Game::increaseNumOfRounds(){
    numOfRounds++;
}

void Game::printLastTurn(){
    cout << gameStatus.back() << endl;
}

void Game::printStats(){
    double winRate = static_cast<double>(player1.getNumOfWinnings()) /getNumOfRounds();
    cout << player1.getName() << " Status- " << "Win Rate: " << winRate <<", "
        << "Cards Won: " << player1.cardesTaken()<< "." << endl;
    winRate = static_cast<double>(player2.getNumOfWinnings()) /getNumOfRounds();
    cout << player2.getName() << " Status- " << "Win Rate: " << winRate <<", "
        << "Cards Won: " << player2.cardesTaken()<< "." << endl;
    double drawRate = static_cast<double>(numOfDraws) /getNumOfRounds();
    cout << "Draw Rate: "<< drawRate << ", Total number of draws: " << numOfDraws <<endl;
}

void Game::printLog(){
    for (unsigned long int i=0; i<gameStatus.size(); i++){
        cout<<gameStatus[i]<<endl;
    }
}

void Game::printWiner(){
    if (player1.cardesTaken() > player2.cardesTaken()){
        cout << player1.getName() <<endl;
    }
    if (player1.cardesTaken() < player2.cardesTaken()){
        cout << player2.getName() <<endl;
    }
    if (player1.cardesTaken() == player2.cardesTaken()){
        cout << "It's a tie" << endl;
    }
}
