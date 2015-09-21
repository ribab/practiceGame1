#ifndef ENTITY_H
#define ENTITY_H

#include "Boundingbox.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Entity {

    public:
        virtual void update(const sf::Window &window, sf::Time tslu);
        virtual void draw(const sf::Window &window);
        virtual void handleInput();
        sf::Vector2f *collides(Entity e);
        void insertBoundingBox(BoundingBox bb, uint32_t index);
        std::vector<sf::Image &> &deleteBoundingBox(uint32_t index);
        void insertAnimation(std::vector<sf::Image> animation, uint32_t index);
        std::vector<sf::Image &> &deleteAnimation(uint32_t index);
        void translate(sf::Vector2f v, bool bounding=true, bool animation=true);
        void setPosition(sf::Vector2f v, bool bounding=true, bool animation=true);

    private:
        std::vector<BoundingBox &> boundingSurface;
        std::vector<std::vector<sf::Image &> &> animations;
        uint32_t currentFrameIdx;
        uint32_t currentAnimationIdx;

};

#endif // ENTITY_H