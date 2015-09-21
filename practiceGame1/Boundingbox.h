#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include<SFML/Graphics.hpp>
#include<assert.h>

class BoundingBox {

    private:
        sf::Shape box;
    public:
        void translate(sf::Vector2f v);
        BoundingBox(){};
        sf::Vector2f *collides(const sf::Shape &object);
        sf::Vector2f *collides_ctc(const sf::Shape &poly1, const sf::Shape &poly2);
        sf::Vector2f *collides_ctp(const sf::Shape &poly1, const sf::Shape &poly2);
        sf::Vector2f *collides_ptp(const sf::Shape &poly1, const sf::Shape &poly2);

};

#endif // BOUNDINGBOX_H