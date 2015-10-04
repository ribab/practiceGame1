#include "Button.hpp"

#include <SFML/Graphics.hpp>

#include "Game.hpp"

Button::Button() {
    // stub
}

Button::Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize,
               sf::Color buttonColor, sf::Color textColor,
               sf::String buttonString,
               std::function<void()> buttonCallback) {

    init(buttonPos, buttonSize,
         buttonColor, textColor,
         buttonString, buttonCallback);

}

void Button::init(sf::Vector2f buttonPos, sf::Vector2f buttonSize,
                  sf::Color buttonColor, sf::Color textColor,
                  sf::String buttonString,
                  std::function<void()> buttonCallback) {

    this->font.loadFromFile("../resource/fonts/arial.ttf");

    this->shape.setSize(buttonSize);
    this->shape.setFillColor(buttonColor);
    this->shape.setPosition(buttonPos);

    this->text.setFont(font);
    this->text.setColor(textColor);
    this->text.setString(buttonString);
    this->text.setCharacterSize(24);
    this->text.setPosition(buttonPos);
    
    this->callback = buttonCallback;

}

void Button::draw() {

    Game::getInst().getWindow().draw(this->shape);
    Game::getInst().getWindow().draw(this->text);

}

bool Button::handleClick() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(Game::getInst().getWindow());
        sf::Vector2f shapePos = shape.getPosition();
        sf::Vector2f shapeSize = shape.getSize();

        if ((mousePos.x >= shapePos.x) &&
                (mousePos.x <= shapePos.x +
                 shapeSize.x) &&
                (mousePos.y >= shapePos.y) &&
                (mousePos.y <= shapePos.y +
                 shapeSize.y)) {

            callback();

            return true;

        }

    }

    return false;

}
