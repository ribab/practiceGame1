#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.hpp"
#include "GameState.hpp"

void Game::pushState(GameState *state) {

    states.push(state);

}

void Game::popState() {

    delete states.top();
    states.pop();

}

GameState *Game::peekState() {

    if (this->states.empty()) {

        return NULL;

    }

    return states.top();

}

void Game::gameLoop(sf::RenderWindow &window) {

    sf::Clock clock;

    while (window.isOpen()) {

        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

        }

        // elapsed time
        sf::Time elapsed = clock.restart();

        // process current state
        if (peekState() == NULL) continue;
        peekState()->handleInput();
        peekState()->update(window, elapsed);
        peekState()->draw(window);

    }

}

Game::Game() {

    // stub

};

Game::Game(sf::RenderWindow &window) {

    // Configure
    sf::VideoMode windowDimensions(650, 650);
    std::string windowName("Simple Pong Game");
    sf::Vector2i windowPosition(static_cast<int>(sf::VideoMode::getDesktopMode().width / 2.0f -
                                                 windowDimensions.width / 2.0f),
                                static_cast<int>(sf::VideoMode::getDesktopMode().height / 2.0f -
                                                 windowDimensions.height / 2.0f));
    int windowStyleBitmask = sf::Style::Close   |
                             sf::Style::Titlebar;

    // Setup
    window.create(windowDimensions, windowName, windowStyleBitmask);
    window.setPosition(windowPosition);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

}

Game::~Game() {

    while (!states.empty()) {

        popState();

    }

}


