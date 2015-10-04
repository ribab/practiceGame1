#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class GameState {

    public:
        virtual void draw() {}
        virtual void update(const sf::Time &tslu) {}
        virtual void handleInput() {}

};

#endif
