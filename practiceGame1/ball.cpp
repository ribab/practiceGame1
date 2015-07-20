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

void Ball::update(const sf::Window &window, // window res
                  sf::Time tslu             // time since last update
                 ) {

    this->shape.move(this->vel.x * tslu.asSeconds(), this->vel.y * tslu.asSeconds());
    sf::Vector2f pos = shape.getPosition();
    if (pos.x <= 0.0f) {

        this->vel.x *= -1.0f;
        pos.x = 0.0f;
        this->shape.setPosition(pos);

    }
    if (pos.x + this->shape.getRadius() * 2.0f >= window.getSize().x) {

        this->vel.x *= -1.0f;
        pos.x = window.getSize().x - this->shape.getRadius() * 2.0f;
        this->shape.setPosition(pos);

    }
    if (pos.y <= 0.0f) {

        this->vel.y *= -1.0f;
        pos.y = 0.0f;
        this->shape.setPosition(pos);

    }
    if (pos.y + this->shape.getRadius() * 2.0f >= window.getSize().y) {

        this->vel.y *= -1.0f;
        pos.y = window.getSize().y - this->shape.getRadius() * 2.0f;
        this->shape.setPosition(pos);

    }

}