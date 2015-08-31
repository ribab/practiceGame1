#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "ball.h"
#include "paddle.h"

#include "GameState.hpp"

class PlayState : public GameState {

    private:
        Ball ball;
        Paddle paddle1;
        Paddle paddle2;
        const float PADDLE_MOVE_TIME = 125.0f;
        int randLatency = 0.0f;
        const int MAX_RAND_LAT = 50.0f;
        float timer = 0.0f;
        Paddle::direction paddle2Dir = Paddle::STILL;
        sf::Font scoreFont;
        sf::Text score1;
        sf::Text score2;

    public:
        PlayState();
        PlayState(const sf::RenderWindow &window);

        void draw(sf::RenderWindow &window);
        void update(const sf::RenderWindow &window,
                    const sf::Time &tslu);
        void handleInput();

};

#endif
