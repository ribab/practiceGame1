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

void Ball::moveAlongVel(sf::Vector2f newPos) {

    sf::Vector2f pos = this->shape.getPosition();

    //move X first
    float alpha = (pos.x - newPos.x) / this->vel.x;
    this->shape.setPosition(newPos.x, (pos.y + vel.y * alpha));

    //now calculate if y still needs to be moved and move it if it does
    float magOfYMove = std::fabs(newPos.y - pos.y);
    if (std::fabs(this->shape.getPosition().y - pos.y) < magOfYMove) {

        pos = this->shape.getPosition();
        float beta = (pos.y - newPos.y) / this->vel.y;
        this->shape.setPosition((pos.x + vel.x * beta), newPos.y);

    }

}

void Ball::update(const sf::Window &window, // window res
                  sf::Time tslu             // time since last update
                 ) {

    this->shape.move(this->vel.x * tslu.asSeconds(), this->vel.y * tslu.asSeconds());
    if (this->shape.getPosition().x <= 0.0f) {

        this->bounce(sf::Vector2f(0.0f, 1.0f));
        this->moveAlongVel(sf::Vector2f(0.0, this->shape.getPosition().y));

    }
    if (this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= window.getSize().x) {

        this->bounce(sf::Vector2f(0.0f, 1.0f));
        this->moveAlongVel(sf::Vector2f(window.getSize().x - this->shape.getRadius() * 2.0f, this->shape.getPosition().y));

    }
    if (this->shape.getPosition().y <= 0.0f) {

        this->bounce(sf::Vector2f(1.0f, 0.0f));
        this->moveAlongVel(sf::Vector2f(this->shape.getPosition().x, 0.0f));

    }
    if (this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= window.getSize().y) {

        this->bounce(sf::Vector2f(1.0f, 0.0f));
        this->moveAlongVel(sf::Vector2f(this->shape.getPosition().x, window.getSize().y - this->shape.getRadius() * 2.0f));

    }

}

sf::Vector2f *Ball::collides(sf::RectangleShape object) {

    for (uint32_t i = 0; i < object.getPointCount(); i++) {

        //Get inward pointing unit vector
        uint32_t j = (i + 1) % object.getPointCount();
        sf::Vector2f unitNormal(object.getPoint(j).x - object.getPoint(i).x, object.getPoint(j).y - object.getPoint(i).y);
        //Rotate by 90.0
        float temp = unitNormal.x;
        unitNormal.x = -1.0f * unitNormal.y;
        unitNormal.y = temp;
        //Normalize
        float normalMag = (float)std::sqrt((unitNormal.x * unitNormal.x) + (unitNormal.y * unitNormal.y));
        unitNormal.x /= normalMag;
        unitNormal.y /= normalMag;

        //Get point on edge of circle
        sf::Vector2f point(this->shape.getPosition().x + this->shape.getRadius() + (unitNormal.x * this->shape.getRadius()),
                           this->shape.getPosition().y + this->shape.getRadius() + (unitNormal.y * this->shape.getRadius()));

        bool collide = true;
        for (uint32_t k; k < object.getPointCount(); k++) {

            //Get vector along edge and vector to point
            uint32_t l = (k + 1) % object.getPointCount();
            sf::Vector2f edgeV(object.getPoint(l).x - object.getPoint(k).x, object.getPoint(l).y - object.getPoint(k).y);
            sf::Vector2f pointV(point.x - object.getPoint(k).x, point.y - object.getPoint(k).y);

            //Rotate by 90 and check if check if dot is > 0
            float dot = (edgeV.x * -1.0f * pointV.y) + (edgeV.y * pointV.x);
            if (dot > 0.0f) {

                collide = false;
                break;

            }

        }

        if (collide)
            //TODO Find the actual distance to move the ball by and return that instead 
            return new sf::Vector2f(-1.0f * this->shape.getRadius(), -1.0f * this->shape.getRadius());

    }

    return NULL;
    /*float min_x = std::numeric_limits<float>::max();
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
    return NULL;*/

}

void Ball::move(sf::Vector2f vector) {

    this->shape.move(vector.x, vector.y);

}

void Ball::bounce(sf::Vector2f unitPlain) {

    //Guarantee that unitPlain is a unit vector
    float unitPlainMag = (float)std::sqrt((unitPlain.x * unitPlain.x) + (unitPlain.y * unitPlain.y));
    unitPlain.x /= unitPlainMag;
    unitPlain.y /= unitPlainMag;

    float dot_v_l = (this->vel.x * unitPlain.x) + (this->vel.y * unitPlain.y);
    float dot_l_l = (unitPlain.x * unitPlain.x) + (unitPlain.y * unitPlain.y);
    float refMag = 2.0f * dot_v_l / dot_l_l;
    this->vel.x = (refMag * unitPlain.x) - vel.x;
    this->vel.y = (refMag * unitPlain.y) - vel.y;

}