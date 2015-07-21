#ifndef BALL_H
#define BALL_H

#include<SFML/Graphics.hpp>
#include<cmath>
#include<limits>

class Ball {

    public:
        Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel);
        ~Ball();
        sf::CircleShape getDrawable();
        void update(const sf::Window &w, sf::Time tslu);
        sf::Vector2f *colides(sf::RectangleShape object);
        void move(sf::Vector2f vector);
        void bouncex();
        void bouncey();

    private:
        sf::CircleShape shape;
        sf::Vector2f vel;

};

#endif // BALL_H