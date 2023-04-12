#include "player.hpp"
#include "string"
#include <exception>
#include <vector>

using namespace ariel;

    Player::Player(){
        string name = "so-and-so";
    };
    Player::Player(string name_){
        string name=name_;
    }

    int Player::stacksize(){
        //the amount of cards that had left to the player
        try{
            if (this->cardsStack == NULL){
                return 0;
            }
            if (cardsStack.size()<=52 && cardsStack.size()>=0){
                return this->cardsStack.size();
            }   
        }
        catch().........
    }

    int Player::cardesTaken(){
        // the amount of cards the player has won until now
        if (wonCardsStack == NULL){
            return 0;
        }
        return wonCardsStack.size();
    }

    string Player::getName(){
        return this->name;
    }

    void Player::increaseNumOfWonCards(){
        numOfWonCards+=2;   //adds the player's card and his opponent
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
    