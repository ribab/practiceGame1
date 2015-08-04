#ifndef PADDLE_H
#define PADDLE_H

#include<SFML/Graphics.hpp>

class Paddle {

    public:
        enum direction{STILL, UP, DOWN};

        Paddle(sf::Vector2f size, sf::Color c, sf::Vector2f startPos, float vel);
        ~Paddle();
        sf::Shape &getDrawable();
        void update(const sf::Window &window, sf::Time tslu);
        void setDirection(direction dir);

    private:
        sf::RectangleShape shape;
        direction dir;
        float vertVel;

};

#endif // PADDLE_H