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
        Paddle paddle2;
        const float PADDLE_MOVE_TIME = 80.0f;
        float timmer = 0.0f;
        Paddle::direction paddle2Dir = Paddle::STILL;

    public:
        PlayState();
        PlayState(const sf::RenderWindow &window);

        void draw(sf::RenderWindow &window);
        void update(const sf::RenderWindow &window,
                    const sf::Time &tslu);
        void handleInput();

};

#endif
