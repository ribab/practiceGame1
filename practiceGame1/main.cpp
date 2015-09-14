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
#include "TitleState.hpp"
#include "Game.hpp"

int main() {

    sf::RenderWindow window;
    Game game(window);

    TitleState titleState(window); 
    game.pushState(&titleState);

    game.gameLoop(window);

    return 0;

}
