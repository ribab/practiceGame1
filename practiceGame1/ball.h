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
        Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel);
        ~Ball();
        sf::CircleShape &getDrawable();
        void update(const sf::Window &w, sf::Time tslu);
        sf::Vector2f *collides(const sf::Shape &object);
        void move(sf::Vector2f vector);
        void moveAlongVel(sf::Vector2f distance, bool forward=false);
        void bounce(sf::Vector2f unitPlain);
        sf::Vector2f getVel();
        
    private:
        sf::Vector2f *collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2);
        sf::Vector2f *collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2);
        sf::Vector2f *collides_ctc(const sf::Shape &poly1, const sf::Shape &poly2);

        sf::CircleShape shape;
        sf::Vector2f vel;

};

#endif // BALL_H