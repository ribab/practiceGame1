#ifndef PADDLE_H
#define PADDLE_H

#include<SFML/Graphics.hpp>

class Paddle {

    public:
        Paddle(sf::Vector2f size, sf::Color c, sf::Vector2f startPos);
        ~Paddle();
        sf::RectangleShape getDrawable();

    private:
        sf::RectangleShape shape;

};

#endif // PADDLE_H