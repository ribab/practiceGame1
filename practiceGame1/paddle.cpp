#include "paddle.h"

Paddle::Paddle(sf::Vector2f size, sf::Color c, sf::Vector2f startPos) {

    this->shape.setSize(size);
    this->shape.setFillColor(c);
    this->shape.setPosition(startPos);

}

Paddle::~Paddle() {}

sf::RectangleShape Paddle::getDrawable() {

    return this->shape;

}