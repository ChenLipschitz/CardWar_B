#include "player.hpp"
#include <string>
#include <exception>
#include <vector>

using namespace std;
using namespace ariel;

    Player::Player(){
        this->name = "so-and-so";
    }
    
    Player::Player(string name_){
        this->name=name_;
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

    std::string Player::getName()const{
        return this->name;
    }

    void Player::increaseNumOfWonCards(){
        numOfWonCards+=2;   //adds the player's card and his opponent
    }

    void Player::increaseNumOfWonCardDraw(){
        numOfWonCards+=4;   
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
    
    void Player::addCardToStack(Card card){
        this->cardsStack.push_back(card);
    }

    Card Player::playCard(){
        Card temp = cardsStack.back();
        cardsStack.pop_back();
        return temp;
    }

    // vector<Card> Player::getStack(){
    //     return this->cardsStack;
    // }

    int Player::getNumOfWinnings(){
        return this->numOfWinnings;
    }