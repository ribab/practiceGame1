#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.hpp"
#include "GameState.hpp"

Game & Game::getInst() {

    static Game instance;
    
    return instance;

}

void Game::pushState(GameState *state) {

    states.push(state);

}

void Game::popState() {

    states.pop();

}

GameState *Game::peekState() {

    if (this->states.empty()) {

        return NULL;

    }

    return states.top();

}

void Game::gameLoop() {

    sf::Clock clock;

    while (getWindow().isOpen()) {

        // handle events
        sf::Event event;
        while (getWindow().pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                getWindow().close();

        }

        // elapsed time
        sf::Time elapsed = clock.restart();

        // process current state
        if (peekState() == NULL) continue;
        peekState()->handleInput();
        peekState()->update(elapsed);
        peekState()->draw();

    }

}

void Game::init(sf::Vector2i windowDimensions,
                sf::String windowName) {

    // Configure
    sf::VideoMode setWindowDimensions(
            windowDimensions.x,
            windowDimensions.y);

    sf::Vector2i windowPosition(
            static_cast<int>(
                sf::VideoMode::getDesktopMode().width / 2.0f -
                setWindowDimensions.width / 2.0f),
            static_cast<int>(
                sf::VideoMode::getDesktopMode().height / 2.0f -
                setWindowDimensions.height / 2.0f));

    int windowStyleBitmask = sf::Style::Close   |
                             sf::Style::Titlebar;

    // Setup
    getWindow().create(setWindowDimensions,
            windowName, windowStyleBitmask);
    getWindow().setPosition(windowPosition);
    getWindow().setVerticalSyncEnabled(true);
    getWindow().setFramerateLimit(60);

}

sf::RenderWindow & Game::getWindow() {

    return window;

}

Game::~Game() {

    while (!states.empty()) {

        popState();

    }

}


