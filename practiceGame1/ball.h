#ifndef BALL_H
#define BALL_H

#include<SFML/Graphics.hpp>
#include<cmath>
#include<math.h>
#include<limits>
#include<iostream>
#include<assert.h>

class Ball {

    public:
        Ball();
        Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel);
        ~Ball();
        sf::Shape &getDrawable();
        void update(sf::Time tslu);
        sf::Vector2f *collides(const sf::Shape &object);
        void move(sf::Vector2f vector);
        void bounce(sf::Vector2f dir);
        sf::Vector2f getVel();
        void changeYVel(sf::Vector2f boundingY);

    private:
        sf::Vector2f *collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2);
        sf::Vector2f *collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2);
        sf::Vector2f *collides_ctc(const sf::Shape &poly1, const sf::Shape &poly2);

        sf::CircleShape shape;
        sf::Vector2f vel;
        float velChange;
        sf::Vector2f minVel;
        sf::Vector2f maxVel;

};

#endif // BALL_H
