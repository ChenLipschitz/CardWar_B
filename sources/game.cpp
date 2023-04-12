
#include "player.hpp"
#include "game.hpp"
#include <iostream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;
using namespace ariel;

Game::Game(Player player1_, Player player2_){
    //if (player1_.getIsPlaying() || player2_.getIsPlaying){
      //  throw ("A player can play only one game");
    //}
    this->player1 = player1_;
    this->player2 = player2_;
    player1.setIsPlaying();
    player2.setIsPlaying();
    handOutCards();
}

void Game::handOutCards(){
    string type1 = "Spades";
    string type2 = "Hearts";
    string type3 = "Diamonds";
    string type4 = "Clubs";

    vector<Cards> deck;
    for (int i=1; i<=13; i++){
        deck.push(Card(i, type1));
        deck.push(Card(i, type2));
        deck.push(Card(i, type3));
        deck.push(Card(i, type4));
    }

    ///check if the deck was created succssesfuly///
    if (deck.size() != 52){
        throw std::runtime_error("ERROR- Couldn't create the deck");
    }

    ///Shuffle- the following 'shuffle' lines were partly taken from chatGPT///
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 g(seed);
    vector<Card> tempVec;
    while (!cardsDeck.empty()) {
        tempVec.push_back(cardsDeck.top());
        deck.pop();
    }
    shuffle(tempVec.begin(), tempVec.end(), g);
    for (const auto& card : tempVec) {
        deck.push(card);
    }

    ///hand out the cards to the players///
    for (int i=1; i<=52; i++){
        Card tempCard = deck.top();
        deck.pop();
        if (i%2 == 1){
            player1.cardsStack.push(tempCard);
        }
        else{
            player2.cardsStack.push(tempCard);
        }
    }
}

void Game::printWiner(){
    if (player1.cardesTaken > player2.cardesTaken){
        cout << player1.getName() <<endl;
    }
    if (player1.cardesTaken < player2.cardesTaken){
        cout << player2.getName() <<endl;
    }
    if (player1.cardesTaken == player2.cardesTaken){
        cout << "It's a tie" << endl;
    }
}

void Game::printStats(){
    //cout << player1.getName() +"status: "+ player1.getNumOfWinnings/player1.getNumOfRounds +
    // cout << player2.getName() +
}

void Game::printLog(){

}

void Game::playTurn(){

    ///preliminary checks///
    if (numOfRounds > 25){
        throw std::runtime_error("ERROR- Game over");
    }
    if (&player1 == &player2){
        throw std::invalid_argument("ERROR- A player cannot play against himself");
    }
    if (player1.stacksize() == 0 || player2.stacksize() == 0){
        throw std::runtime_error("ERROR- Game was over");
    }

    int result = player1.cardsStack.top().compareTo(player2.cardsStack.top());
    player1.cardsStack.pop();
    player2.cardsStack.pop();
    if (result == 1){
        player1.increaseNumOfWonCards();
        increaseNumOfRounds();
        return;
    }
    else if (result == -1){
        player2.increaseNumOfWonCards();
        increaseNumOfRounds();
        return;
    }
    else{
        int numOfTies = 0;
        ///incase one of the decks were is 0 during the draw////
        while(result == 0){
            numOfTies++;
            if (numOfTies > 1){
                player1.cardsStack.pop();
                player2.cardsStack.pop();
            }
            result = player1.cardsStack.top().compareTo(player2.cardsStack.top());
        }
        if (result == 1){
            for(int i=1; i<=numOfTies; i++){
                player1.increaseNumOfWonCards();
                increaseNumOfRounds();
                return;
            }
        }
        else{
            for(int i=1; i<=numOfTies; i++){
                player2.increaseNumOfWonCards();
                increaseNumOfRounds();
                return;
            }
        }
    }
}


void Game::playAll(){
    while(player1.cardsStack.size() > 0 || player2.cardsStack.size() > 0){
        this->playTurn();
    }
}

int Game::getNumOfRounds(){
    return this->numOfRounds;
}

void Game::increaseNumOfRounds(){
    numOfRounds++;
}

void Game::printLastTurn(){
    cout << gameStatus.top() << endl;
}

