#include "paddle.h"
#include "Game.hpp"

Paddle::Paddle(sf::Vector2f size, sf::Color c, sf::Vector2f startPos, float vel) {

    this->shape.setSize(size);
    this->shape.setFillColor(c);
    this->shape.setPosition(startPos);
    this->dir = STILL;
    this->vertVel = vel;

}

sf::Shape &Paddle::getDrawable() {

    return static_cast<sf::Shape &>(this->shape);

}

void Paddle::update(sf::Time tslu) {

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
    if (pos.y + this->shape.getSize().y >= Game::getInst().getWindow().getSize().y) {

        pos.y = Game::getInst().getWindow().getSize().y - this->shape.getSize().y;
        this->shape.setPosition(pos);

    }

}

void Paddle::setDirection(Paddle::direction dir) {

    this->dir = dir;

}

Paddle::direction Paddle::getDirection() {

    return this->dir;

}
