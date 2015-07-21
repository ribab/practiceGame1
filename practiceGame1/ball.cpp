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

sf::Vector2f *Ball::colides(sf::RectangleShape object) {

    float min_x = std::numeric_limits<float>::max();
    float min_y = std::numeric_limits<float>::max();
    bool xcolides = false;
    bool ycolides = false;
    if (this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= object.getPosition().y &&
        this->shape.getPosition().y <= object.getPosition().y + object.getSize().y &&
        this->shape.getPosition().x <= object.getPosition().x + object.getSize().x &&
        this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= object.getPosition().x + object.getSize().x) {

        xcolides = true;
        float xDist =  (object.getPosition().x + object.getSize().x) - this->shape.getPosition().x;
        if (fabs(xDist) < fabs(min_x))
            min_x = xDist;

    }
    if (this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= object.getPosition().y &&
        this->shape.getPosition().y <= object.getPosition().y + object.getSize().y &&
        this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= object.getPosition().x &&
        this->shape.getPosition().x <= object.getPosition().x) {

        xcolides = true;
        float xDist = object.getPosition().x - (this->shape.getPosition().x + this->shape.getRadius() * 2.0f);
        if (fabs(xDist) < fabs(min_x))
            min_x = xDist;

    }
    if (this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= object.getPosition().x &&
        this->shape.getPosition().x <= object.getPosition().x + object.getSize().x &&
        this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= object.getPosition().y &&
        this->shape.getPosition().y <= object.getPosition().y) {

        ycolides = true;
        float yDist =  object.getPosition().y - (this->shape.getPosition().y + this->shape.getRadius() * 2.0f);
        if (fabs(yDist) < fabs(min_y))
            min_y = yDist;

    }
    if (this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= object.getPosition().x &&
        this->shape.getPosition().x <= object.getPosition().x + object.getSize().x &&
        this->shape.getPosition().y <= object.getPosition().y + object.getSize().y &&
        this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= object.getPosition().y + object.getSize().y) {

        ycolides = true;
        float yDist = (object.getPosition().y + object.getSize().y) - this->shape.getPosition().y;
        if (fabs(yDist) < fabs(min_y))
            min_y = yDist;

    }

    if (xcolides && !ycolides)
        min_y = 0.0f;
    if (!xcolides && ycolides)
        min_x = 0.0f;
    if (xcolides || ycolides)
        return new sf::Vector2f(min_x, min_y);
    return NULL;

}

void Ball::move(sf::Vector2f vector) {

    this->shape.move(vector.x, vector.y);

}

void Ball::bouncex() {

    this->vel.x *= -1.0f;

}

void Ball::bouncey() {

    this->vel.y *= -1.0f;

}