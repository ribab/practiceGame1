#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button {

    public:
        Button();
        Button(sf::Vector2f buttonPos, sf::Vector2f buttonSize,
               sf::Color buttonColor, sf::Color textColor,
               sf::String buttonString,
               std::function<void()> buttonCallback);

//        ~Button();

        void init(sf::Vector2f buttonPos, sf::Vector2f buttonSize,
                  sf::Color buttonColor, sf::Color textColor,
                  sf::String buttonString,
                  std::function<void()> buttonCallback);

        void draw();
        
        bool handleClick();

    private:
        sf::Text text;
        sf::RectangleShape shape;
        sf::Font font;
        std::function<void()> callback;

};

#endif 
