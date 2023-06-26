#ifndef WAR_H
#define WAR_H

// Things I want to happen
// 1. cards get dealt evenly between computer and player
// 2. computer plays first
// 3. check rank
// 3.1 if rank higher take both cards and give to appropriate player
// 3.2 else WAR!!!
// 3.2.1 Both players place down two cards. the last card to be placed is the one you eval
// 3.2.2 Loop until a player wins the pile
// 4. The game ends when one of the players has 52 cards

// Things I need to make this happen
// The players each need a hand
// I need a constant, 26, for half of the deck
// I need a function to start the game (play)
// I need a function to place cards
// Instead of making a war function, just place cards in a loop until 
// one of the cards checked is higher
// I'm gonna need two piles for each player
// I need a pick up function that takes in a player

#include <stack>
#include <vector>
#include "card.h"

#define HANDLEN 26

class war {
public:
	war();
	~war();
public:
	void play();
protected:
	std::stack<Card*> pickUp();
	Card* flip(std::deque<Card*>, std::stack<Card*>);
    void printCards(std::stack<Card*>);
protected:
    std::deque<Card*> playerHand;
    std::deque<Card*> computerHand;

    std::stack<Card*> playerPile;
    std::stack<Card*> computerPile;
};

#endif