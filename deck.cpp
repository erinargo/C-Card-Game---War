#include "deck.h"

#include <random>

static std::random_device rd;
static std::mt19937 rng(rd());

Deck::Deck() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            Card *card = new Card(Card::Suit(i), Card::Value(j));
            this->deck.push_back(card);
        }
    }
}

Deck::~Deck() {
    for(int i = 0; i < deck.size(); i++) {
        delete this->deck[i];
    }
}

Card *Deck::draw() {
    Card *card = shuffled.top();
    this->shuffled.pop();
    return card;
}

void Deck::shuffle() {
    while(!shuffled.empty()) {
        shuffled.pop();
    }

    std::shuffle(this->deck.begin(), this->deck.end(), rng);

    for(int i = 0; i < deck.size(); i++) {
        this->shuffled.push(this->deck[i]);
    }
}