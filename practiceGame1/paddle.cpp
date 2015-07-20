#include "paddle.h"

Paddle::Paddle(sf::Vector2f size, sf::Color c, sf::Vector2f startPos, float vel) {

    this->shape.setSize(size);
    this->shape.setFillColor(c);
    this->shape.setPosition(startPos);
    this->dir = STILL;
    this->vertVel = vel;

}

Paddle::~Paddle() {}

sf::RectangleShape Paddle::getDrawable() {

    return this->shape;

}

void Paddle::update(const sf::Window &window, sf::Time tslu) {

    if (this->dir == UP) {

        this->shape.move(0.0f, -1.0f * this->vertVel * tslu.asSeconds());
        this->dir = STILL;

    }
    if (this->dir == DOWN) {

        this->shape.move(0.0f, this->vertVel * tslu.asSeconds());
        this->dir = STILL;

    }

    sf::Vector2f pos = shape.getPosition();
    if (pos.y <= 0.0f) {

        pos.y = 0.0f;
        this->shape.setPosition(pos);

    }
    if (pos.y + this->shape.getSize().y >= window.getSize().y) {

        pos.y = window.getSize().y - this->shape.getSize().y;
        this->shape.setPosition(pos);

    }

}

void Paddle::setDirection(Paddle::direction dir) {

    this->dir = dir;

}