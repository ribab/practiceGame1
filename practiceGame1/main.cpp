#include <SFML/Graphics.hpp>
#include "ball.h"
#include "paddle.h"

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

        b.moveAlongVel(sf::Vector2f(b.getDrawable().getPosition().x + least->x, b.getDrawable().getPosition().y + least->y));
        if (std::fabs(least->x) > 0.0f)
            b.bounce(sf::Vector2f(0.0f, 1.0f));
        if (std::fabs(least->y) > 0.0f)
            b.bounce(sf::Vector2f(1.0f, 0.0f));
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
    Ball ball(ballR, sf::Color(255, 255, 255, 255), sf::Vector2f((window.getSize().x / 2.0f) - ballR, (window.getSize().y / 2.0f) - ballR), sf::Vector2f(300.0f, -150.0f));

    sf::Vector2f paddleSize(10.0f, window.getSize().y / 7.0f);
    Paddle paddle1(paddleSize, sf::Color(255, 255, 255, 255), sf::Vector2f(paddleSize.x * 20.0f + 10.0f, window.getSize().y / 2.0f - paddleSize.y / 2.0f), 750.0f);

    sf::Clock gameClock;

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