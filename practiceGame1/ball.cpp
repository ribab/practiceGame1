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

void Ball::moveAlongVel(sf::Vector2f distance) {

    sf::Vector2f pos = this->shape.getPosition();
    sf::Vector2f newPos(pos.x + distance.x, pos.y + distance.y);

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
        this->moveAlongVel(sf::Vector2f(0.0f - this->shape.getPosition().x, 0.0f));

    }
    if (this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= window.getSize().x) {

        this->bounce(sf::Vector2f(0.0f, 1.0f));
        this->moveAlongVel(sf::Vector2f(window.getSize().x - this->shape.getPosition().x - this->shape.getRadius() * 2.0f, 0.0));

    }
    if (this->shape.getPosition().y <= 0.0f) {

        this->bounce(sf::Vector2f(1.0f, 0.0f));
        this->moveAlongVel(sf::Vector2f(0.0f, 0.0f - this->shape.getPosition().y));

    }
    if (this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= window.getSize().y) {

        this->bounce(sf::Vector2f(1.0f, 0.0f));
        this->moveAlongVel(sf::Vector2f(0.0f, window.getSize().y - this->shape.getPosition().y - this->shape.getRadius() * 2.0f));

    }

}

sf::Vector2f *Ball::collides(sf::RectangleShape object) {

    bool globalCollide = false;
    float minMag = std::numeric_limits<float>::max();
    float maxMag = 0.0f;
    sf::Vector2f least(0.0f, 0.0f);
    sf::Vector2f most(0.0f, 0.0f);
    sf::Vector2f center(this->shape.getPosition().x + this->shape.getRadius(),
                        this->shape.getPosition().y + this->shape.getRadius());

    for (uint32_t i = 0; i < object.getPointCount(); i++) {

        sf::Vector2f currentVert(object.getPoint(i).x + object.getPosition().x, object.getPoint(i).y + object.getPosition().y);
        float xDist = currentVert.x - center.x;
        float yDist = currentVert.y - center.y;
        float dist = (float)std::sqrt((xDist) * (xDist) + (yDist) * (yDist));
        if (dist <= this->shape.getRadius()) {

            globalCollide = true;
            sf::Vector2f circlePoint((xDist / dist * this->shape.getRadius()) + center.x, (yDist / dist * this->shape.getRadius()) + center.y);
            float distX = currentVert.x - circlePoint.x;
            float distY = currentVert.y - circlePoint.y;
            float mag  = (float)std::sqrt((distX * distX) + (distY * distY));
            if (mag > maxMag) {

                most.x = distX;
                most.y = distY;
                maxMag = mag;

            }

        }

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
        sf::Vector2f point(center.x + (unitNormal.x * this->shape.getRadius()),
                           center.y + (unitNormal.y * this->shape.getRadius()));

        bool collide = true;
        for (uint32_t k = 0; k < object.getPointCount(); k++) {

            //Get vector along edge and vector to point
            uint32_t l = (k + 1) % object.getPointCount();
            sf::Vector2f edgeV(object.getPoint(l).x - object.getPoint(k).x, object.getPoint(l).y - object.getPoint(k).y);
            sf::Vector2f pointV(point.x - object.getPoint(k).x - object.getPosition().x, point.y - object.getPoint(k).y - object.getPosition().y);

            //Rotate by 90 and check if check if dot is > 0
            if ((edgeV.x * -1.0f * pointV.y) + (edgeV.y * pointV.x) > 0.0f) {

                collide = false;
                break;

            }

        }

        if (collide) {

            globalCollide = true;
            sf::Vector2f point1(currentVert.x, currentVert.y);
            sf::Vector2f point2(object.getPoint(j).x + object.getPosition().x, object.getPoint(j).y + object.getPosition().y);          
            sf::Vector2f point3(center.x, center.y);
            sf::Vector2f point4(point.x, point.y);

            float x1y2_y1x2 = (point1.x * point2.y) - (point1.y * point2.x);
            float x3y4_y3x4 = (point3.x * point4.y) - (point3.y * point4.x);
            float denom = ((point1.x - point2.x) * (point3.y - point4.y)) - ((point1.y - point2.y) * (point3.x - point4.x));

            assert(denom >= std::numeric_limits<float>::min() ||
                   denom <= (-1.0f * std::numeric_limits<float>::min()));

            sf::Vector2f crossPoint(((x1y2_y1x2 * (point3.x - point4.x)) - ((point1.x - point2.x) * x3y4_y3x4)) / denom,
                                    ((x1y2_y1x2 * (point3.y - point4.y)) - ((point1.y - point2.y) * x3y4_y3x4)) / denom);

            //std::cout << "index i: " << i << "\tcrossX:  " << crossPoint.x << "\tcrossY:  " << crossPoint.y << std::endl;
            //std::cout << "          \tpointX:  " << point.x << "\tpointY:  " << point.y << std::endl;
            //std::cout << "          \tcenterX: " << center.x << "\tcenterY: " << center.y << std::endl;

            float distX = crossPoint.x - point.x;
            float distY = crossPoint.y - point.y;
            float mag  = (float)std::sqrt((distX * distX) + (distY * distY));
            if (mag < minMag) {

                least.x = distX;
                least.y = distY;
                minMag = mag;

            }
            
            //std::cout << "          \tleastX:  " << least.x << "\tleastY:  " << least.y << std::endl;

        }

    }

    if (globalCollide) {

        float leastMag  = (float)std::sqrt((least.x * least.x) + (least.y * least.y));
        float mostMag  = (float)std::sqrt((most.x * most.x) + (most.y * most.y));
        if (leastMag > mostMag)
            return new sf::Vector2f(least.x, least.y);
        else
            return new sf::Vector2f(most.x, most.y);

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

sf::Vector2f Ball::getVel() {

    return this->vel;

}