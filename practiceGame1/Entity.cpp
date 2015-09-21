#include "Entity.h"

void Entity::translate(sf::Vector2f v, bool bounding, bool animation) {

    if (bounding)
        for (std::vector<BoundingBox &>::iterator it = boundingSurface.begin(); it != boundingSurface.end(); ++it)
            (*it).translate(v);

}

void Entity::setPosition(sf::Vector2f v, bool bounding, bool animation) {

    

}