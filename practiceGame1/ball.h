#ifndef BALL_H
#define BALL_H

#include<SFML/Graphics.hpp>

class Ball {

    public:
        Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel);
        sf::CircleShape getDrawable();
        ~Ball();
        
    private:
        sf::CircleShape shape;
        sf::Vector2f vel;

};

#endif // BALL_H