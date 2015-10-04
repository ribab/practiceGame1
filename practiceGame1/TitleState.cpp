// include SFML
#include <SFML/Graphics.hpp>

// include local classes
#include "ball.h"
#include "paddle.h"
#include "Game.hpp"
#include "PlayState.hpp"

// include header file
#include "TitleState.hpp"

void startButtonCallback()
{
    static PlayState playState;
    Game::getInst().pushState(&playState);
}

void quitButtonCallback()
{
    // does nothing for now
}

TitleState::TitleState() {
    this->init();
}

void TitleState::init() {

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

void TitleState::draw() {

    Game::getInst().getWindow().clear(sf::Color::Black);

    startButton.draw();
    quitButton.draw();

    Game::getInst().getWindow().display();

}

void TitleState::update(const sf::Time &tslu) {


}

void TitleState::handleInput() {

    startButton.handleClick();
    quitButton.handleClick();

}
