#include "ball.h"

Ball::Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel) {

    this->shape.setRadius(r);
    this->shape.setFillColor(c);
    this->shape.setPosition(startPos);
    this->vel.x = startVel.x;
    this->vel.y = startVel.y;

}

Ball::~Ball() {}

sf::CircleShape Ball::getDrawable() {

    return this->shape;

}