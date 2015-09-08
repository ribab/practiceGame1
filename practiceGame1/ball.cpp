#include "ball.h"
#include <stdint.h>
#include <typeinfo>
#include <assert.h>

Ball::Ball(float r, sf::Color c, sf::Vector2f startPos, sf::Vector2f startVel) {

    this->shape.setRadius(r);
    this->shape.setFillColor(c);
    this->shape.setPosition(startPos);
    this->vel.x = startVel.x;
    this->vel.y = startVel.y;
    this->velChange = 5.0f;
    this->minVel.x = 150.0f;
    this->minVel.y = 150.0f;
    this->maxVel.x = 600.0f;
    this->maxVel.y = 600.0f;
    moveState = false;

}

sf::Shape &Ball::getDrawable() {

    return this->shape;

}

void Ball::update(const sf::Window &window, // window res
                  sf::Time tslu             // time since last update
                 ) {

    if (moveState) {

        this->shape.move(this->vel.x * tslu.asSeconds(), this->vel.y * tslu.asSeconds());
        if (this->shape.getPosition().x <= 0.0f || this->shape.getPosition().x + this->shape.getRadius() * 2.0f >= window.getSize().x)
            moveState = false;
        if (this->shape.getPosition().y <= 0.0f) {

            this->move(sf::Vector2f(0.0f, 0.0f - this->shape.getPosition().y));
            this->bounce(sf::Vector2f(0.0f, 1.0f));

        }
        if (this->shape.getPosition().y + this->shape.getRadius() * 2.0f >= window.getSize().y) {

            this->move(sf::Vector2f(0.0f, window.getSize().y - this->shape.getPosition().y - this->shape.getRadius() * 2.0f));
            this->bounce(sf::Vector2f(0.0f, -1.0f));

        }
        
    }

}

void Ball::handleInput() {

    if (!moveState &&sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        moveState = true;

}

sf::Vector2f *Ball::collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2) {

    assert(typeid(poly1) != typeid(sf::CircleShape));
    assert(typeid(poly2) != typeid(sf::CircleShape));

    sf::Vector2f *least = new sf::Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    float minGap = std::numeric_limits<float>::max();
    uint32_t normalsLen = poly1.getPointCount() + poly2.getPointCount();
    sf::Vector2f unitNormals[normalsLen];

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
        unitNormal.y = tempX;
        unitNormals[i] = unitNormal;

    }
    for (uint32_t i = 0; i < poly2.getPointCount(); i++) {

        uint32_t j = (i + 1) % poly2.getPointCount();
        sf::Vector2f currentVertex(poly2.getPoint(i).x + poly2.getPosition().x, poly2.getPoint(i).y + poly2.getPosition().y);
        sf::Vector2f adjacentVertex(poly2.getPoint(j).x + poly2.getPosition().x, poly2.getPoint(j).y + poly2.getPosition().y);
        sf::Vector2f unitNormal(adjacentVertex.x - currentVertex.x, adjacentVertex.y - currentVertex.y);
        float magnitude = static_cast<float>(std::sqrt(unitNormal.x * unitNormal.x + unitNormal.y * unitNormal.y));
        unitNormal.x /= magnitude;
        unitNormal.y /= magnitude;
        //Rotate by 90
        float tempX = unitNormal.x;
        unitNormal.x = -1.0f * unitNormal.y;
        unitNormal.y = tempX;
        unitNormals[i + poly1.getPointCount()] = unitNormal;

    }

    //sf::Vector2f collideVert1;
    //sf::Vector2f collideVert2;
    for (uint32_t i = 0; i < normalsLen; i++) {

        sf::Vector2f unitNormal = unitNormals[i];

        float minPoint1 = std::numeric_limits<float>::max();
        float maxPoint1 = -1.0f * std::numeric_limits<float>::max();
        //sf::Vector2f tempCollideVert1;
        for (uint32_t k = 0; k < poly1.getPointCount(); k++) {

            sf::Vector2f vertex(poly1.getPoint(k).x + poly1.getPosition().x, poly1.getPoint(k).y + poly1.getPosition().y);
            float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;
            if (point < minPoint1) {

                minPoint1 = point;
                //tempCollideVert1.x = vertex.x;
                //tempCollideVert1.y = vertex.y;

            }
            if (point > maxPoint1)
                maxPoint1 = point;

        }

        float minPoint2 = std::numeric_limits<float>::max();
        float maxPoint2 = -1.0f * std::numeric_limits<float>::max();
        sf::Vector2f tempCollideVert2;
        for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

            sf::Vector2f vertex(poly2.getPoint(k).x + poly2.getPosition().x, poly2.getPoint(k).y + poly2.getPosition().y);
            float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;
            if (point < minPoint2)
                minPoint2 = point;
            if (point > maxPoint2) {

                maxPoint2 = point;
                //tempCollideVert2.x = vertex.x;
                //tempCollideVert2.y = vertex.y;

            }

        }

        float gap = 0.0f;
        if ((minPoint2 >= minPoint1 && minPoint2 <= maxPoint1) ||//min2 is inside 1
            (maxPoint1 >= minPoint2 && maxPoint1 <= maxPoint2))  //max1 is inside 2
            gap = minPoint2 - maxPoint1;
        else if ((maxPoint2 >= minPoint1 && maxPoint2 <= maxPoint1) ||//max2 is inside 1
                 (minPoint1 >= minPoint2 && minPoint1 <= maxPoint2))  //min1 is inside 2
            gap = maxPoint2 - minPoint1;
        else
            return NULL;

        if (std::fabs(gap) < std::fabs(minGap)) {

            minGap = gap;
            least->x = unitNormal.x * minGap;
            least->y = unitNormal.y * minGap;
            /*collideVert1.x = tempCollideVert1.x;
            collideVert1.y = tempCollideVert1.y;
            collideVert2.x = tempCollideVert2.x;
            collideVert2.y = tempCollideVert2.y;*/

        }

    }

    return least; //collideVert1, collideVert2

}

sf::Vector2f *Ball::collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2) {

    assert(typeid(poly1) == typeid(sf::CircleShape));
    assert(typeid(poly2) != typeid(sf::CircleShape));

    sf::CircleShape circle = *dynamic_cast<const sf::CircleShape *>(&poly1);

    sf::Vector2f center(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());
    float minDist = std::numeric_limits<float>::max();
    sf::Vector2f circleNormal;

    sf::Vector2f *least = new sf::Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    float minGap = std::numeric_limits<float>::max();
    uint32_t normalsLen = poly2.getPointCount() + 1;
    sf::Vector2f unitNormals[normalsLen];

    for (uint32_t i = 0; i < poly2.getPointCount(); i++) {

        uint32_t j = (i + 1) % poly2.getPointCount();
        sf::Vector2f currentVertex(poly2.getPoint(i).x + poly2.getPosition().x, poly2.getPoint(i).y + poly2.getPosition().y);

        float xDiff = (currentVertex.x - center.x);
        float yDiff = (currentVertex.y - center.y);
        float distance = xDiff * xDiff + yDiff * yDiff;
        if (distance < minDist) {

            minDist = distance;
            circleNormal.x = xDiff;
            circleNormal.y = yDiff;
            float mag = static_cast<float>(std::sqrt(distance));
            circleNormal.x /= mag;
            circleNormal.y /= mag;

        }

        sf::Vector2f adjacentVertex(poly2.getPoint(j).x + poly2.getPosition().x, poly2.getPoint(j).y + poly2.getPosition().y);
        sf::Vector2f unitNormal(adjacentVertex.x - currentVertex.x, adjacentVertex.y - currentVertex.y);
        float magnitude = static_cast<float>(std::sqrt(unitNormal.x * unitNormal.x + unitNormal.y * unitNormal.y));
        unitNormal.x /= magnitude;
        unitNormal.y /= magnitude;
        //Rotate by 90
        float tempX = unitNormal.x;
        unitNormal.x = -1.0f * unitNormal.y;
        unitNormal.y = tempX;
        unitNormals[i] = unitNormal;

    }
    unitNormals[poly2.getPointCount()] = circleNormal;

    for (uint32_t i = 0; i < normalsLen; i++) {

        sf::Vector2f unitNormal = unitNormals[i];

        float dot = center.x * unitNormal.x + center.y * unitNormal.y;
        float minPoint1 = dot - circle.getRadius();
        float maxPoint1 = dot + circle.getRadius();
        if (minPoint1 > maxPoint1) {

            float temp = minPoint1;
            minPoint1 = maxPoint1;
            maxPoint1 = temp;

        }

        float minPoint2 = std::numeric_limits<float>::max();
        float maxPoint2 = -1.0f * std::numeric_limits<float>::max();
        for (uint32_t k = 0; k < poly2.getPointCount(); k++) {

            sf::Vector2f vertex(poly2.getPoint(k).x + poly2.getPosition().x, poly2.getPoint(k).y + poly2.getPosition().y);
            float point = vertex.x * unitNormal.x + vertex.y * unitNormal.y;
            if (point < minPoint2)
                minPoint2 = point;
            if (point > maxPoint2)
                maxPoint2 = point;

        }

        float gap = 0.0f;
        if ((minPoint2 >= minPoint1 && minPoint2 <= maxPoint1) ||//min2 is inside 1
            (maxPoint1 >= minPoint2 && maxPoint1 <= maxPoint2))  //max1 is inside 2
            gap = minPoint2 - maxPoint1;
        else if ((maxPoint2 >= minPoint1 && maxPoint2 <= maxPoint1) ||//max2 is inside 1
                 (minPoint1 >= minPoint2 && minPoint1 <= maxPoint2))  //min1 is inside 2
            gap = maxPoint2 - minPoint1;

        else
            return NULL;

        if (std::fabs(gap) < std::fabs(minGap)) {

            minGap = gap;
            least->x = unitNormal.x * minGap;
            least->y = unitNormal.y * minGap;

        }

    }

    return least;

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

void Ball::setPos(sf::Vector2f vector) {

    this->shape.setPosition(vector);

}

void Ball::bounce(sf::Vector2f dir) {

    if ((dir.x < 0.0f && this->vel.x > 0.0f) ||
        (dir.x > 0.0f && this->vel.x < 0.0f))
        this->vel.x *= -1.0f;
    if ((dir.y < 0.0f && this->vel.y > 0.0f) ||
        (dir.y > 0.0f && this->vel.y < 0.0f))
        this->vel.y *= -1.0f;

}

sf::Vector2f Ball::getVel() {

    return this->vel;

}

void Ball::changeYVel(sf::Vector2f boundingY) {

    if (boundingY.x > boundingY.y) {

        float tempX = boundingY.x;
        boundingY.x = boundingY.y;
        boundingY.y = tempX;

    }

    float centerY = shape.getPosition().y + shape.getRadius();
    float midPoint = boundingY.x + (boundingY.y - boundingY.x) / 2.0f;
    if (centerY <= midPoint) {

        float quarterPoint = boundingY.x + (midPoint - boundingY.x) / 2.0f;
        if (vel.y > 0.0f)
            vel.y += (quarterPoint - centerY) * velChange;
        else
            vel.y -= (quarterPoint - centerY) * velChange;

    }
    else if (centerY > midPoint) {

        float quarterPoint = midPoint + (boundingY.y - midPoint) / 2.0f;
        if (vel.y > 0.0f)
            vel.y += (centerY - quarterPoint) * velChange;
        else
            vel.y -= (centerY - quarterPoint) * velChange;

    }

    if (std::fabs(vel.y) < minVel.y) {

        float velYTemp = vel.y;
        vel.y = minVel.y;
        if (velYTemp < 0)
            vel.y *= -1.0f;

    }

    if (std::fabs(vel.y) > maxVel.y) {

        float velYTemp = vel.y;
        vel.y = maxVel.y;
        if (velYTemp < 0)
            vel.y *= -1.0f;

    }

}