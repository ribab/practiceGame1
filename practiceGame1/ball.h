#ifndef BALL_H
#define BALL_H

#include<SFML/Graphics.hpp>
#include<cmath>
#include<math.h>
#include<limits>

class Ball {

    public:
        Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel);
        ~Ball();
        sf::CircleShape getDrawable();
        void update(const sf::Window &w, sf::Time tslu);
        sf::Vector2f *collides(sf::RectangleShape object);
        void move(sf::Vector2f vector);
        void moveAlongVel(sf::Vector2f newPos);
        void bounce(sf::Vector2f unitPlain);
        
    private:
        sf::CircleShape shape;
        sf::Vector2f vel;

};

#endif // BALL_H