#include "player.hpp"
#include "string"
#include <exception>
#include <vector>

using namespace ariel;

    Player::Player(){
        string name = "so-and-so";
    }
    
    Player::Player(string name_){
        string name=name_;
    }

    int Player::stacksize(){
        //the amount of cards that had left to the player
        if (cardsStack.size()<=52 && cardsStack.size()>=0){
            return this->cardsStack.size();
        }
        else{
            throw std::runtime_error("ERROR- cannot get the stack size");
        }   
    }

    int Player::cardesTaken(){
        // the amount of cards the player won until now
        return this->numOfWonCards;
    }

    string Player::getName(){
        return this->name;
    }

    void Player::increaseNumOfWonCards(){
        numOfWonCards+=2;   //adds the player's card and his opponent
    }

    void Player::increaseNumOfWonCard(){
        numOfWonCards++;   //adds the player's card
    }

    void Player::increaseNumOfWinnings(){
        numOfWinnings++;
    }

    bool Player::getIsPlaying(){
        return this->isPlaying;
    }

    void Player::setIsPlaying(){
        if(isPlaying){
            this->isPlaying = false;
        }
        else{
            this->isPlaying = true;
        }
    }
    
    void Player::addCardToStack(Card c){
        this->cardsStack.push_back(c);
    }

    vector<Card> Player::getStack(){
        return this->cardsStack;
    }

    int Player::getNumOfWinnings(){
        return this->numOfWinnings;
    }