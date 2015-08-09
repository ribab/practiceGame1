#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "paddle.h"

#include "GameState.hpp"

class PlayState : public GameState {

    private:
        Ball ball;
        Paddle paddle1;

    public:
        PlayState();
        PlayState(const sf::RenderWindow &window);

        void draw(sf::RenderWindow &window);
        void update(const sf::RenderWindow &window,
                    const sf::Time &tslu);
        void handleInput();

};

#endif
