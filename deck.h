#ifndef UNTITLED_DECK_H
#define UNTITLED_DECK_H

#endif //UNTITLED_DECK_H

#include <vector>
#include <stack>
#include <random>
#include <algorithm>

#include "card.h"

class Deck {
public:
    Deck();
    ~Deck();
public:
    void shuffle();
    Card* draw();
protected:
    std::vector<Card*> deck;
    std::stack<Card*> shuffled;
};
