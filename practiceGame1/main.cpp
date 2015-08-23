// SFML includes
#include <SFML/Graphics.hpp>

// Global includes
#include <string>
#include <iostream>
#include <typeinfo>

// Local includes
#include "ball.h"
#include "paddle.h"
#include "PlayState.hpp"
#include "Game.hpp"

int main() {

    sf::RenderWindow window;
    Game game(window);

    PlayState playState(window);
    game.pushState(&playState);

    game.gameLoop(window);

    return 0;

}
