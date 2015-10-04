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

    Game::getInst().init(
              sf::Vector2i(640,480),
              sf::String("Yet Another Pong Game"));

    TitleState titleState;
    Game::getInst().pushState((GameState *) &titleState);

    Game::getInst().gameLoop();

    return 0;

}
