// include SFML
#include <SFML/Graphics.hpp>

// include local classes
#include "ball.h"
#include "paddle.h"

// include header file
#include "PlayState.hpp"

PlayState::PlayState() {
    // stub
}

PlayState::PlayState(const sf::RenderWindow &window) {

    // Creating Ball
    float ballRadius = 2.0f;
    sf::Color ballColor(255, 255, 255, 255);
    sf::Vector2f ballStartPos(
            (window.getSize().x / 2.0f) - ballRadius,
            (window.getSize().y / 2.0f) - ballRadius);
    sf::Vector2f ballStartSpeed(300.0f, -150.0f);    
//    ball = Ball(ballRadius, ballColor,
//              ballStartPos, ballStartSpeed);
    
    // Creating Paddle
    sf::Vector2f paddleSize(500.0f, 10.0f);
    sf::Color paddleColor(255, 255, 255, 255);
    sf::Vector2f paddleStartPos(
        80.0f,
        window.getSize().y / 2.0f - paddleSize.y / 2.0f);
    float paddleStartSpeed = 650.0f;
    paddle1 = Paddle(paddleSize, paddleColor,
                   paddleStartPos, paddleStartSpeed);

}

void PlayState::draw(sf::RenderWindow &window) {

    window.clear(sf::Color::Black);
    window.draw(ball.getDrawable());
    window.draw(paddle1.getDrawable());
    window.display();

}

void PlayState::update(const sf::RenderWindow &window,
                       const sf::Time &tslu) {

    ball.update(window, tslu);
    paddle1.update(window, tslu);

    sf::Vector2f *least = ball.collides(paddle1.getDrawable());
    if (least != NULL) {

        ball.moveAlongVel(sf::Vector2f(least->x, least->y));
        if ((ball.getVel().x < 0.0f && least->x >= 0.0f) ||
            (ball.getVel().x >= 0.0f && least->x < 0.0f) ||
            (ball.getVel().y < 0.0f && least->y >= 0.0f) ||
            (ball.getVel().y >= 0.0f && least->y < 0.0f))
            ball.bounce(sf::Vector2f(least->y, -1.0f * least->x));
        delete least;
        least = NULL;

    }

}

void PlayState::handleInput() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        paddle1.setDirection(Paddle::UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        paddle1.setDirection(Paddle::DOWN);

}
