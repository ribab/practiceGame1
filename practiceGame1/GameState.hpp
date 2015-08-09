#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

class GameState {

    public:
        virtual void draw(sf::RenderWindow &window) {}
        virtual void update(const sf::RenderWindow &window,
                            const sf::Time &tslu) {}
        virtual void handleInput() {}

};

#endif
