
#include "player.hpp"
#include "game.hpp"
#include "card.hpp"
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
        tempVec.push_back(cardsDeck.back());
        deck.pop();
    }
    shuffle(tempVec.begin(), tempVec.end(), g);
    for (const auto& card : tempVec) {
        deck.push(card);
    }

    ///hand out the cards to the players///
    for (int i=1; i<=52; i++){
        Card tempCard = deck.back();
        deck.pop();
        if (i%2 == 1){
            player1.cardsStack.push(tempCard);
        }
        else{
            player2.cardsStack.push(tempCard);
        }
    }
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

    int result = player1.cardsStack.back().compareTo(player2.cardsStack.back());
    string state = player1.getName()+" played "+ player1.cardsStack.back().toString() +" "
                player2.getName()+" played "+player2.cardsStack.back().toString();
    player1.cardsStack.pop();
    player2.cardsStack.pop();
    
    ///player1 wins///
    if (result == 1){
        player1.increaseNumOfWonCards();
        player1.increaseNumOfWinnings();
        increaseNumOfRounds();
        gameStatus.push(state+". "+player1.getName()+" wins.");
        return;
    }
    ///player2 wins///
    else if (result == -1){
        player2.increaseNumOfWonCards();
        player2.increaseNumOfWinnings();
        increaseNumOfRounds();
        gameStatus.push(state+". "+player2.getName()+" wins.");
        return;
    }
    ///Tie///
    else{
        int numOfTies = 0;
        ///incase one of the decks were is 0 during the draw////
        while(result == 0){
            state = state + ". Draw. ";
            numOfTies++;
            if (numOfTies > 1){
                player1.cardsStack.pop();
                player2.cardsStack.pop();
            }
            result = player1.cardsStack.back().compareTo(player2.cardsStack.back());
            state = state + player1.getName()+" played "+ player1.cardsStack.back().toString() +" "
                player2.getName()+" played "+player2.cardsStack.back().toString();
        }
        numOfDraws = numOfDraws + numOfTies;
        if (result == 1){
            for(int i=1; i<=numOfTies; i++){
                player1.increaseNumOfWonCards();
                increaseNumOfRounds();
                return;
            }
            gameStatus.push(state+". "+player1.getName()+" wins.");
            player1.increaseNumOfWinnings();
        }
        else{
            for(int i=1; i<=numOfTies; i++){
                player2.increaseNumOfWonCards();
                increaseNumOfRounds();
                return;
            }
            gameStatus.push(state+". "+player2.getName()+" wins.");
            player2.increaseNumOfWinnings();
        }
    }
}


void Game::playAll(){
    while(player1.cardsStack.size() > 0 && player2.cardsStack.size() > 0){
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
    for (int i=0; i<gameStatus.size(); i++){
        cout<<gameStatus[i]<<endl;
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
