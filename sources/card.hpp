#pragma once
#include <iostream>
using namespace std;

namespace ariel{
    class Card{
        private:
        int value;
        string shape;

        public:
        Card(int value, string shape);
        int getValue();
        string getShape();
        string toString();
    };
}