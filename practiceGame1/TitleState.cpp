// include SFML
#include <SFML/Graphics.hpp>

// include local classes
#include "ball.h"
#include "paddle.h"

// include header file
#include "TitleState.hpp"

void startButtonCallback()
{
    // does nothing for now
}

void quitButtonCallback()
{
    // does nothing for now
}

TitleState::TitleState() {
    // stub
}

TitleState::TitleState(const sf::RenderWindow &window) {

    init(window);

}

void TitleState::init(const sf::RenderWindow &window) {

    static sf::Vector2f buttonSize(100, 25);
    static sf::Color buttonColor(255, 255, 255 ,255);
    static sf::Color textColor(100, 100, 100, 255);

    static sf::Vector2f startButtonPosition(100, 100);
    static sf::String startButtonText("Start");
    startButton.init(startButtonPosition, buttonSize, buttonColor, textColor, startButtonText, startButtonCallback);

    static sf::Vector2f quitButtonPosition(100, 200);
    static sf::String quitButtonText = "Quit";
    quitButton.init(quitButtonPosition, buttonSize, buttonColor, textColor, quitButtonText, quitButtonCallback);

}

void TitleState::draw(sf::RenderWindow &window) {

    window.clear(sf::Color::Black);

    startButton.draw(window);
    quitButton.draw(window);

    window.display();

}

void TitleState::update(const sf::RenderWindow &window,
                       const sf::Time &tslu) {


}

void TitleState::handleInput() {

    startButton.handleClick();
    quitButton.handleClick();

}
