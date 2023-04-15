
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
    
}

///used GeeksForGeeks
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
    if (player1.cardesTaken() + player2.cardesTaken() == 52){
        throw std::runtime_error("ERROR- Game was over");
    }

    Card cardPlayer1= player1.playCard();
    Card cardPlayer2= player2.playCard();
    int result = dualTurn(cardPlayer1, cardPlayer2);
    string state = player1.getName()+" played "+ cardPlayer1.toString() +" "+
                player2.getName()+" played "+cardPlayer2.toString();
    
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
            // in case the deck is empty
            if (player1.stacksize() == 0){
                for (int i=0; i<numOfTies-1; i++){
                    player1.increaseNumOfWonCards();
                    player2.increaseNumOfWonCards();
                }
                player1.addCardWon();
                player2.addCardWon();
                increaseNumOfRounds();
                return;
            }
            // in case only 1 card has left in the deck- the upside down card
            if (player1.stacksize() == 1){
                player1.playCard();
                player2.playCard();
                for (int i=0; i<numOfTies; i++){
                    player1.increaseNumOfWonCards();
                    player2.increaseNumOfWonCards();
                }
                return;
            }

            //pop cards only if there are more than 2 cards in the deck (for upside down card and open card)
            if (player1.stacksize() >= 2 ){
                player1.playCard();
                player2.playCard();
            }
            Card cardPlayer1D= player1.playCard();
            Card cardPlayer2D= player2.playCard();
            result = dualTurn(cardPlayer1D, cardPlayer2D);
            state = state + player1.getName()+" played "+ cardPlayer1D.toString() +" "+
                player2.getName()+" played "+cardPlayer2D.toString();
        }
        ///end of loop///

        numOfDraws = numOfDraws + numOfTies;
        ///player1 won the draw///
        if (result == 1){
            player1.increaseNumOfWonCards();
            for(int i=1; i<=numOfTies; i++){
                player1.increaseNumOfWonCardDraw();
                increaseNumOfRounds();
            }
            gameStatus.push_back(state+". "+player1.getName()+" wins.");
            player1.increaseNumOfWinnings();
            return;
        }

        ///player2 won the draw///
        if (result == -1){
            player2.increaseNumOfWonCards();
            for(int i=1; i<=numOfTies; i++){
                player2.increaseNumOfWonCardDraw();
                increaseNumOfRounds();
            }
            gameStatus.push_back(state+". "+player2.getName()+" wins.");
            player2.increaseNumOfWinnings();
            return;
        }
    }
}

int Game::dualTurn(Card card1, Card card2){
    if (card1.getValue() == card2.getValue()){ 
        return 0;
    }
    if (card1.getValue() == 1 && card2.getValue() != 2){    //Ace agaist 3-13-> Ace wins
        return 1;
    }
    if (card1.getValue() != 2 && card2.getValue() == 1){     //Ace against 3-13-> Ace wins
        return -1;
    }
    if(card1.getValue() > card2.getValue()){    
        return 1;
    }
    if (card1.getValue() < card2.getValue()){
        return -1;
    }
    else{
        throw std::runtime_error("ERROR- cannot compare cards");
    }
}


void Game::playAll(){
    if (player1.stacksize() == 0 && player2.stacksize() == 0){
        throw std::runtime_error("ERROR- the deck is empty");
    }
    while(player1.stacksize() > 0 && player2.stacksize() > 0){
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
        cout << player1.getName()<< " Won!!!" <<endl;
    }
    if (player1.cardesTaken() < player2.cardesTaken()){
        cout << player2.getName() << " Won!!!" <<endl;
    }
    if (player1.cardesTaken() == player2.cardesTaken()){
        cout << "It's a tie" << endl;
    }
}
