#include <iostream>

#include "war.h"
#include "deck.h"

war::war() {
	// Nope
}

war::~war() {

}

// Pushes onto the pile and returns top card which is then immediately handled inline and pushed onto its respective
//stack

Card*  war::flip(std::deque<Card*> hand, std::stack<Card*> pile) {
    pile.push(hand.back());

    return pile.top();
}

// returns a completed hand of cards composed of both piles which is handled inline where it is pushed into the correct hand
// this handles clearing the piles when necessary

std::stack<Card*> war::pickUp() {
    std::stack<Card*> hand;
    while(!computerPile.empty()) {
        hand.push(computerPile.top());
        computerPile.pop();
    }

    while(!playerPile.empty()) {
        hand.push(playerPile.top());
        playerPile.pop();
    }

    return hand;
}

// The bulk of the code. Rather than define a function to handle war, it was easier to handle it as a plain loop with
// a condition at the end that adds another card onto the pile which isn't cleared until someone picks it up
// first it deals the cards and then we enter the main loop where the computer flips first and then pushes onto
// its pile. The result is printed. When printing, I have defined a new public bool in card.cpp called hidden
// if hidden is true (AKA if the condition at the end of the loop returns a war and pushes an extra card, that card is
// set to hidden.) then the printed output will be "*****". The last item in computerHand is then popped. Repeat for
// player. Not super eloquent but I couldn't think of any better way to do it. The cards are then compared and the piles
// are picked up by the winner and pushed to the front of the hand. I figured it was simple enough to also reset
// the hidden values here while I'm iterating over the only cards that could have had the value changed.

// The last while statement just confirms if the user still wants to play.

void war::play() {
    std::string playerName;

	Deck deck;
    deck.shuffle();

    std::cout << "Hello, welcome to war! Please enter your name: " << std::endl;
    std::cin >> playerName;

    for(int i = 0; i < HANDLEN; i++) {
        playerHand.push_back(deck.draw());
    }

    for(int j = 0; j < HANDLEN; j++) {
        computerHand.push_back(deck.draw());
    }

    while(computerHand.size() >= 0 && playerHand.size() >= 0) {
        std::string continuePlaying;

        // Computer plays
        Card *ComputerCard = war::flip(computerHand, computerPile);

        computerPile.push(ComputerCard);

        std::cout << "Computer played: " << std::endl;

        war::printCards(computerPile);
        computerHand.pop_back();

        // Player plays
        Card *PlayerCard = war::flip(playerHand, playerPile);
        playerPile.push(PlayerCard);

        std::cout << "\nYou played: " << std::endl;

        war::printCards(playerPile);
        playerHand.pop_back();

        // Cards are compared
        if(PlayerCard->compareValue(*ComputerCard) == 1) {
            std::stack<Card*> cards = pickUp();
            while(!cards.empty()) {
                cards.top()->hidden = false;

                playerHand.push_front(cards.top());
                cards.pop();
            }

            std::cout << "\nYou won with " << std::endl;
            PlayerCard->print();
            std::cout << " against " << std::endl;
            ComputerCard->print();

        } else if(PlayerCard->compareValue(*ComputerCard) == -1) {
            std::stack<Card*> cards = pickUp();
            while(!cards.empty()) {
                cards.top()->hidden = false;

                computerHand.push_front(cards.top());
                cards.pop();
            }

            std::cout << "\nThe computer won with " << std::endl;
            ComputerCard->print();
            std::cout << " against " << std::endl;
            PlayerCard->print();
        } else {
            // If the cards aren't picked up, the pile stays the same so I can just add onto it here and let the loop
            // continue.

            // Also checks if one or the other player can continue with the war. If they can't, the opposite player has their hand drained and the loop breaks
            std::cout << "War!!!" << std::endl;
            if(computerHand.size() >= 3) {
                Card *ComputerCard = war::flip(computerHand, computerPile);
                ComputerCard->hidden = true;

                computerPile.push(ComputerCard);
                computerHand.pop_back();
            } else {
                while(!playerHand.empty()) {
                    playerHand.pop_back();
                }

                break;
            }

            if(playerHand.size() >= 3) {
                Card *PlayerCard = war::flip(playerHand, playerPile);

                PlayerCard->hidden = true;

                playerPile.push(PlayerCard);
                playerHand.pop_back();
            } else {
                while(!computerHand.empty()) {
                    computerHand.pop_back();
                }

                break;
            }
        }

        // Asks to continue. Really happy I was going to do this regardless of the assignment. For some reason, even though
        // all the logic works correctly, I can never seem to have one player or the other win. They just both equal out
        while(continuePlaying != "Y" && continuePlaying != "y" && continuePlaying != "N" && continuePlaying != "n") {
            std::cout << "\nYour hand: "
                      << playerHand.size() << "\nThe computer's hand: " << computerHand.size() << std::endl;
            std::cout << "\nWould you like to continue playing? Y/N" << std::endl;
            std::cin >> continuePlaying;
        }

        if(continuePlaying == "N" || continuePlaying == "n") break;
    }

    if(computerHand.size() == 52) std::cout << "The computer won!" << std::endl;
    else if(playerHand.size() == 52) std::cout << "You won!" << std::endl;
    std::cout << "Thank you for playing " << playerName << "!" << std::endl;
}

// Prints a stack, in this case I use it to print the pile so you can clearly see what's going on
// Unfortunately that means the print is in reverse so it's not super easy to read.
void war::printCards(std::stack<Card *> cards) {
    while(!cards.empty()) {
        std::cout << "Card #" << cards.size() << ": " << std::endl;
        cards.top()->print();
        cards.pop();
    }
}