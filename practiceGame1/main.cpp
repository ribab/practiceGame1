#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paddle.h"
#include <iostream>
#include <typeinfo>

void handleInput(Paddle &paddle1) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        paddle1.setDirection(Paddle::UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        paddle1.setDirection(Paddle::DOWN);

}

void update(const sf::RenderWindow &window, sf::Time tslu, Ball &b, Paddle &paddle1) {

    b.update(window, tslu);
    paddle1.update(window, tslu);

    sf::Vector2f *least = b.collides(paddle1.getDrawable());
    if (least != NULL) {

        //b.moveAlongVel(sf::Vector2f(least->x, least->y));
        b.move(sf::Vector2f(least->x, least->y));
        b.bounce(sf::Vector2f(least->y, -1.0f * least->x));

        delete least;
        least = NULL;

    }

}

int main() {

    sf::RenderWindow window(sf::VideoMode(650, 650), "Simple Pong game", sf::Style::Close | sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2.0f - window.getSize().x/2.0f, sf::VideoMode::getDesktopMode().height / 2.0f - window.getSize().y/2.0f));
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    float ballR = 10.0f;
    Ball ball(ballR, sf::Color(255, 255, 255, 255), sf::Vector2f((window.getSize().x / 2.0f) - ballR, (window.getSize().y / 2.0f) - ballR), sf::Vector2f(350.0f, -150.0f));
    
    sf::Vector2f paddleSize(10.0f, window.getSize().y / 7.0f);
    Paddle paddle1(paddleSize, sf::Color(255, 255, 255, 255), sf::Vector2f(80.0f, window.getSize().y / 2.0f - paddleSize.y), 650.0f);
    //ball.move(sf::Vector2f(-1.0f * ball.getDrawable().getPosition().x + paddle1.getDrawable().getPosition().x + paddle1.getDrawable().getSize().x / 2.0f - ball.getDrawable().getRadius(),
    //                       -1.0f * ball.getDrawable().getPosition().y + paddle1.getDrawable().getPosition().y + paddle1.getDrawable().getSize().y - ball.getDrawable().getRadius() * 2.0f));
    sf::Clock gameClock;

    //sf::RectangleShape recShape = paddle1.getDrawable();
    /*sf::Vector2f *least = ball.collides(paddle1.getDrawable());
    if (least != NULL) {

        std::cout << "x: " << least->x << "\ty: " << least->y << std::endl;
        delete least;
        least = NULL;

    }*/

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

        }

        handleInput(paddle1);
        update(window, gameClock.restart(), ball, paddle1);
        window.clear();
        window.draw(ball.getDrawable());
        window.draw(paddle1.getDrawable());
        window.display();

    }

    return 0;

}