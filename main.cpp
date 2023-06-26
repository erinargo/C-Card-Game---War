#include <iostream>

#include "deck.h"
#include "war.h"

int main(int argc, char **argv)
{
    srand(time(NULL));
    war war;
    war.play();

    std::cout << std::endl;

    return 1;
}