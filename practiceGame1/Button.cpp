#include "Button.hpp"

#include <SFML/Graphics.hpp>

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

void Button::draw(sf::RenderWindow &window) {

    window.draw(this->shape);
    window.draw(this->text);

}

bool Button::handleClick() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        sf::Vector2i mousePos = sf::Mouse::getPosition();

        if ((mousePos.x >= shape.getPosition().x) &&
                (mousePos.x <= shape.getPosition().x +
                 shape.getSize().x) &&
                (mousePos.y >= shape.getPosition().y) &&
                (mousePos.y <= shape.getPosition().y +
                 shape.getSize().y)) {

            callback();

            return true;

        }

    }

    return false;

}
