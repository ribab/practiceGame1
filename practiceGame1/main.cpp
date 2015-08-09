// SFML includes
#include <SFML/Graphics.hpp>

// Global includes
#include <iostream>
#include <string>

// Local includes
#include "ball.h"
#include "paddle.h"
#include "PlayState.hpp"

int main() {

    // Create Window
    sf::VideoMode windowDimensions(650, 650);
    std::string windowName("Simple Pong Game");
    int windowStyleBitmask = sf::Style::Close   |
                             sf::Style::Titlebar;
    sf::RenderWindow window(windowDimensions,
                            windowName,
                            windowStyleBitmask);
    sf::Vector2i windowPosition(
            sf::VideoMode::getDesktopMode().width/2.0f -
                window.getSize().x/2.0f,
            sf::VideoMode::getDesktopMode().height/2.0f -
                window.getSize().y/2.0f);
    window.setPosition(windowPosition);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    // Create Clock
    sf::Clock gameClock;

    // Create PlayState
    PlayState playState(window);
    GameState *currentState = &playState; // TODO: make stack
    
    while (window.isOpen()) {
        // Game Loop

        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

        }

        // process currentState
        currentState->handleInput();

        currentState->update(window,
                             gameClock.restart());

        currentState->draw(window);

    }

    return 0;

}
