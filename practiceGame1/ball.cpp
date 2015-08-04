#include "ball.h"
#include <typeinfo>
#include <assert.h>

Ball::Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel) {

    this->shape.setRadius(r);
    this->shape.setFillColor(c);
    this->shape.setPosition(startPos);
    this->vel.x = startVel.x;
    this->vel.y = startVel.y;

}

Ball::~Ball() {}

sf::CircleShape &Ball::getDrawable() {

    return this->shape;

}

void Ball::moveAlongVel(sf::Vector2f distance, bool forward/*=false*/) {

    if (this->vel.x > -1.0f * std::numeric_limits<float>::min() &&
        this->vel.x < std::numeric_limits<float>::min()) {

        this->shape.move(distance.x, 0.0f);
        distance.x = 0.0f;

    }
    if (this->vel.y > -1.0f * std::numeric_limits<float>::min() &&
        this->vel.y < std::numeric_limits<float>::min()) {

        this->shape.move(0.0, distance.y);
        distance.y = 0.0f;

    }

    sf::Vector2f v(-1.0f * this->vel.x, -1.0f * this->vel.y);
    if (forward) {

        v.x *= -1.0f;
        v.y *= -1.0f;

    }

    if ((v.x > 0.0f && distance.x < 0.0f) ||
        (v.x < 0.0f && distance.x > 0.0f)) {

        this->shape.move(distance.x, 0.0f);
        distance.x = 0.0f;

    }
    if ((v.y > 0.0f && distance.y < 0.0f) ||
        (v.y < 0.0f && distance.y > 0.0f)) {

        this->shape.move(0.0f, distance.y);
        distance.y = 0.0f;

    }

    float alpha = 0.0f;
    float beta = 0.0f;
    if (v.x <= -1.0f * std::numeric_limits<float>::min() ||
        v.x >= std::numeric_limits<float>::min())
        alpha = distance.x / v.x;
    if (v.y <= -1.0f * std::numeric_limits<float>::min() ||
        v.y >= std::numeric_limits<float>::min())
        beta = distance.y / v.y;
    assert(alpha >= 0.0f && beta >= 0.0f);

    if (alpha >= beta)
        this->shape.move(v.x * alpha, v.y * alpha);
    else
        this->shape.move(v.y * beta, v.y * beta);

}

void Ball::update(const sf::Window &window, // window res
                  sf::Time tslu             // time since last update
                 ) {

    this->shape.move(this->vel.x * tslu.asSeconds(), this->vel.y * tslu.asSeconds());
    if (this->shape.getPosition().x <= 0.0f) {

        this->moveAlongVel(sf::Vector2f(0.0f - this->shape.getPosition().x, 0.0f));
        this->bounce(sf::Vector2f(0.0f, 1.0f));
        //this->move(sf::Vector2f(0.0f - this->shape.getPosition().x, 0.0f));

    }
    if (this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= window.getSize().x) {

        this->moveAlongVel(sf::Vector2f(window.getSize().x - this->shape.getPosition().x - this->shape.getRadius() * 2.0f, 0.0));
        this->bounce(sf::Vector2f(0.0f, 1.0f));
        //this->move(sf::Vector2f(window.getSize().x - this->shape.getPosition().x - this->shape.getRadius() * 2.0f, 0.0));

    }
    if (this->shape.getPosition().y <= 0.0f) {

        this->moveAlongVel(sf::Vector2f(0.0f, 0.0f - this->shape.getPosition().y));
        this->bounce(sf::Vector2f(1.0f, 0.0f));
        //this->move(sf::Vector2f(0.0f, 0.0f - this->shape.getPosition().y));

    }
    if (this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= window.getSize().y) {

        this->moveAlongVel(sf::Vector2f(0.0f, window.getSize().y - this->shape.getPosition().y - this->shape.getRadius() * 2.0f));
        this->bounce(sf::Vector2f(1.0f, 0.0f));
        //this->move(sf::Vector2f(0.0f, window.getSize().y - this->shape.getPosition().y - this->shape.getRadius() * 2.0f));

    }

}

sf::Vector2f *Ball::collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2) {

    assert(typeid(poly1) != typeid(sf::CircleShape));
    assert(typeid(poly2) != typeid(sf::CircleShape));

    sf::Vector2f *least = new sf::Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    float minGap = std::numeric_limits<float>::max();
    for (uint32_t i = 0; i < poly1.getPointCount(); i++) {

        uint32_t j = (i + 1) % poly1.getPointCount();
        sf::Vector2f currentVertex(poly1.getPoint(i).x + poly1.getPosition().x, poly1.getPoint(i).y + poly1.getPosition().y);
        sf::Vector2f adjacentVertex(poly1.getPoint(j).x + poly1.getPosition().x, poly1.getPoint(j).y + poly1.getPosition().y);
        sf::Vector2f unitNormal(adjacentVertex.x - currentVertex.x, adjacentVertex.y - currentVertex.y);
        float magnitude = static_cast<float>(std::sqrt(unitNormal.x * unitNormal.x + unitNormal.y * unitNormal.y));
        unitNormal.x /= magnitude;
        unitNormal.y /= magnitude;
        //Rotate by 90
        float tempX = unitNormal.x;
        unitNormal.x = -1.0f * unitNormal.y;
        unitNormal.y = unitNormal.x;

        float minPoint1 = std::numeric_limits<float>::max();
        float maxPoint1 = 0.0f;
        for (uint32_t k = 0; k < poly1.getPointCount(); k++) {

            sf::Vector2f vertex(poly1.getPoint(k).x + poly1.getPosition().x, poly1.getPoint(k).y + poly1.getPosition().y);
            float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;
            if (std::fabs(point) < std::fabs(minPoint1))
                minPoint1 = point;
            if (std::fabs(point) > std::fabs(maxPoint1))
                maxPoint1 = point;

        }

        float minPoint2 = std::numeric_limits<float>::max();
        float maxPoint2 = 0.0f;
        for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

            sf::Vector2f vertex(poly2.getPoint(k).x + poly2.getPosition().x, poly2.getPoint(k).y + poly2.getPosition().y);
            float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;
            if (std::fabs(point) < std::fabs(minPoint1))
                minPoint2 = point;
            if (std::fabs(point) > std::fabs(maxPoint1))
                maxPoint2 = point;

        }
        if (minPoint2 > maxPoint1) {

            float gap = (minPoint2 - maxPoint1);
            if (gap < minGap) {

                minGap = gap;
                least->x = minPoint2 * unitNormal.x - maxPoint1 * unitNormal.x;
                least->y = minPoint2 * unitNormal.y - maxPoint1 * unitNormal.y;

            }

        }
        else if(minPoint1 > maxPoint2) {

            float gap = (minPoint1 - maxPoint2);
            if (gap < minGap) {

                minGap = gap;
                least->x = minPoint2 * unitNormal.x - maxPoint1 * unitNormal.x;
                least->y = minPoint2 * unitNormal.y - maxPoint1 * unitNormal.y;

            }

        }
        else
            return NULL;

    }

    return least;

}

sf::Vector2f *Ball::collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2) {

    sf::CircleShape circle;
    if (typeid(poly1) == typeid(sf::CircleShape)) {

        assert(typeid(poly2) != typeid(sf::CircleShape));
        circle = *dynamic_cast<const sf::CircleShape *>(&poly1);

    }
    else {

        assert(typeid(poly2) == typeid(sf::CircleShape));
        assert(typeid(poly1) != typeid(sf::CircleShape));
        circle = *dynamic_cast<const sf::CircleShape *>(&poly2);

    }

    return NULL;

}

sf::Vector2f *Ball::collides_ctc(const sf::Shape &poly1, const sf::Shape &poly2) {

    assert(typeid(poly1) == typeid(sf::CircleShape));
    assert(typeid(poly2) == typeid(sf::CircleShape));

    const sf::CircleShape circle1 = *dynamic_cast<const sf::CircleShape *>(&poly1);
    const sf::CircleShape circle2 = *dynamic_cast<const sf::CircleShape *>(&poly2);

    sf::Vector2f center1(circle1.getPosition().x + circle1.getRadius(), circle1.getPosition().y + circle1.getRadius());
    sf::Vector2f center2(circle2.getPosition().x + circle2.getRadius(), circle2.getPosition().y + circle2.getRadius());

    float xDiff = (center2.x - center1.x);
    float yDiff = (center2.y - center1.y);
    float dist = xDiff * xDiff + yDiff * yDiff;
    float rSum = circle1.getRadius() + circle2.getRadius();
    if (dist <= (rSum * rSum)) {

        //Get both vectors
        sf::Vector2f centerVect1(xDiff, yDiff);
        sf::Vector2f centerVect2(center1.x - center2.x, center1.y - center2.y);

        //calculate Magnitudes
        float centerVectMag1 = static_cast<float>(std::sqrt(centerVect1.x * centerVect1.x + centerVect1.y * centerVect1.y));
        float centerVectMag2 = static_cast<float>(std::sqrt(centerVect2.x * centerVect2.x + centerVect2.y * centerVect2.y));

        //Locate Points on circles
        sf::Vector2f circlePoint1((centerVect1.x / centerVectMag1 * circle1.getRadius()) + center1.x,
                                  (centerVect1.y / centerVectMag1 * circle1.getRadius()) + center1.y);
        sf::Vector2f circlePoint2((centerVect2.x / centerVectMag2 * circle2.getRadius()) + center2.x,
                                  (centerVect2.y / centerVectMag2 * circle2.getRadius()) + center2.y);

        return new sf::Vector2f(circlePoint2.x - circlePoint1.x, circlePoint2.y - circlePoint1.y);

    }

    return NULL;

}

sf::Vector2f *Ball::collides(const sf::Shape &object) {

    if (typeid(object) != typeid(sf::CircleShape))
        return this->collides_ctp(static_cast<sf::Shape &>(this->shape), object);
    return this->collides_ctc(static_cast<sf::Shape &>(this->shape), object);

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