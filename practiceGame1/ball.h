#ifndef BALL_H
#define BALL_H

#include<SFML/Graphics.hpp>

class Ball {

    public:
        Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel);
        ~Ball();
        sf::CircleShape getDrawable();
        void update(const sf::Window &w, sf::Time tslu);

    private:
        sf::CircleShape shape;
        sf::Vector2f vel;

};

#endif // BALL_H