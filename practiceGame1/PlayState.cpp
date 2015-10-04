// include SFML
#include <SFML/Graphics.hpp>

// include local classes
#include "ball.h"
#include "paddle.h"
#include "Game.hpp"

// include header file
#include "PlayState.hpp"

PlayState::PlayState() {

    std::srand(std::time(NULL));

    // Creating Paddle
    sf::Vector2f paddleSize(10.0f, Game::getInst().getWindow().getSize().y / 7.0f);
    sf::Color paddleColor(255, 255, 255, 255);
    sf::Vector2f paddleStartPos(
        80.0f,
        Game::getInst().getWindow().getSize().y / 2.0f - paddleSize.y / 2.0f);
    float paddleStartSpeed = 650.0f;
    paddle1 = Paddle(paddleSize, paddleColor,
                     paddleStartPos, paddleStartSpeed);

    paddle2 = Paddle(paddleSize, paddleColor,
                     sf::Vector2f(Game::getInst().getWindow().getSize().x - paddleStartPos.x - paddleSize.x, paddleStartPos.y),
                     paddleStartSpeed);

    // Creating Ball
    float ballRadius = 10.0f;
    sf::Color ballColor(255, 255, 255, 255);
    sf::Vector2f ballStartPos(paddleStartPos.x + paddleSize.x,
                              paddleStartPos.y + (paddleSize.y / 2.0f) - ballRadius);
    sf::Vector2f ballStartSpeed(300.0f, -150.0f);    
    ball = Ball(ballRadius, ballColor, ballStartPos, ballStartSpeed);

    if (!scoreFont.loadFromFile("../resource/fonts/arial.ttf"))
        std::cout << "Font did not load!" << std::endl;
    scoreOffset.x = 30.0f;
    scoreOffset.y = 20.0f;
    score1 = 0;
    score1Text.setFont(scoreFont);
    score1Text.setString("0");
    score1Text.setCharacterSize(24);
    score1Text.setColor(sf::Color::Red);
    score1Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    score1Text.setPosition(scoreOffset.x - score1Text.getLocalBounds().width / 2.0f,
                           scoreOffset.y - score1Text.getLocalBounds().height / 2.0f);

    score2 = 0;
    score2Text.setFont(scoreFont);
    score2Text.setString("0");
    score2Text.setCharacterSize(24);
    score2Text.setColor(sf::Color::Red);
    score2Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    score2Text.setPosition(Game::getInst().getWindow().getSize().x - scoreOffset.x - score2Text.getLocalBounds().width / 2.0f,
                           scoreOffset.y - score2Text.getLocalBounds().height / 2.0f);

    serveText.setFont(scoreFont);
    serveText.setString("To Serve, Press the Space Bar.");
    serveText.setCharacterSize(24);
    serveText.setColor(sf::Color::Red);
    serveText.setStyle(sf::Text::Bold);
    serveText.setPosition(Game::getInst().getWindow().getSize().x / 2.0f - serveText.getLocalBounds().width / 2.0f,
                          Game::getInst().getWindow().getSize().y / 2.0f - serveText.getLocalBounds().height / 2.0f);

}

void PlayState::draw() {

    Game::getInst().getWindow().clear(sf::Color::Black);
    Game::getInst().getWindow().draw(ball.getDrawable());
    Game::getInst().getWindow().draw(paddle1.getDrawable());
    Game::getInst().getWindow().draw(paddle2.getDrawable());
    Game::getInst().getWindow().draw(score1Text);
    Game::getInst().getWindow().draw(score2Text);
    
    sf::RectangleShape paddle1Drawable = *dynamic_cast<const sf::RectangleShape *>(&(paddle1.getDrawable()));
    sf::CircleShape circle = *dynamic_cast<const sf::CircleShape *>(&(ball.getDrawable()));
    if (!ball.getMoveState() &&
        (circle.getPosition().x == paddle1Drawable.getPosition().x + paddle1Drawable.getSize().x))
        Game::getInst().getWindow().draw(serveText);

    Game::getInst().getWindow().display();

}

void PlayState::update(const sf::Time &tslu) {

    ball.update(tslu);
    paddle1.update(tslu);
    paddle2.update(tslu);

    sf::CircleShape circle = *dynamic_cast<const sf::CircleShape *>(&(ball.getDrawable()));
    sf::RectangleShape paddle1Drawable = *dynamic_cast<const sf::RectangleShape *>(&(paddle1.getDrawable()));
    sf::RectangleShape paddle2Drawable = *dynamic_cast<const sf::RectangleShape *>(&(paddle2.getDrawable()));
    if (circle.getPosition().x + circle.getRadius() * 2.0f >= Game::getInst().getWindow().getSize().x) {

        score1++;
        ball.setPos(sf::Vector2f(paddle1Drawable.getPosition().x + paddle1Drawable.getSize().x,
                                 paddle1Drawable.getPosition().y + (paddle1Drawable.getSize().y / 2.0f) - circle.getRadius()));
        score1Text.setString(std::to_string(score1));
        score1Text.setPosition(scoreOffset.x - score1Text.getLocalBounds().width / 2.0f,
                               scoreOffset.y - score1Text.getLocalBounds().height / 2.0f);

    }
    if (circle.getPosition().x <= 0.0f) {

        score2++;
        ball.setPos(sf::Vector2f(paddle2Drawable.getPosition().x - circle.getRadius() * 2.0f,
                                 paddle2Drawable.getPosition().y + (paddle2Drawable.getSize().y / 2.0f) - circle.getRadius()));
        ball.bounce(sf::Vector2f(-1.0f, 0.0f));
        score2Text.setString(std::to_string(score2));
        score2Text.setPosition(Game::getInst().getWindow().getSize().x - scoreOffset.x - score2Text.getLocalBounds().width / 2.0f,
                               scoreOffset.y - score2Text.getLocalBounds().height / 2.0f);

    }

    if (!ball.getMoveState()) {

        if (ball.getDrawable().getPosition().x == paddle1Drawable.getPosition().x + paddle1Drawable.getSize().x)
            ball.setPos(sf::Vector2f(paddle1Drawable.getPosition().x + paddle1Drawable.getSize().x,
                                     paddle1Drawable.getPosition().y + (paddle1Drawable.getSize().y / 2.0f) - circle.getRadius()));
        else {

            serveTimer += tslu.asSeconds();
            ball.setPos(sf::Vector2f(paddle2Drawable.getPosition().x - circle.getRadius() * 2.0f,
                                     paddle2Drawable.getPosition().y + (paddle2Drawable.getSize().y / 2.0f) - circle.getRadius()));

        }

    }

    aiTimer += tslu.asMilliseconds();
    if (aiTimer >= (PADDLE_MOVE_TIME + randLatency)) {

        randLatency = std::rand() % (MAX_RAND_LAT + 1);
        aiTimer = 0.0f;
        sf::RectangleShape rectangle = *dynamic_cast<const sf::RectangleShape *>(&(paddle2.getDrawable()));
        if (circle.getPosition().y + circle.getRadius() < rectangle.getPosition().y + rectangle.getSize().y / 3.0f) {

            paddle2.setDirection(Paddle::UP);
            paddle2Dir = Paddle::UP;

        }
        else if (circle.getPosition().y + circle.getRadius() > rectangle.getPosition().y + 2.0f * rectangle.getSize().y / 3.0f) {

            paddle2.setDirection(Paddle::DOWN);
            paddle2Dir = Paddle::DOWN;

        }
        else {

            paddle2.setDirection(Paddle::STILL);
            paddle2Dir = Paddle::STILL;

        }

    }
    else
        paddle2.setDirection(paddle2Dir);

    if (ball.getMoveState()) {

        sf::Vector2f *least = ball.collides(paddle1Drawable);
        if (least != NULL) {

            ball.move(sf::Vector2f(least->x, least->y));
            ball.bounce(sf::Vector2f(least->x, least->y));
            ball.changeYVel(sf::Vector2f(paddle1Drawable.getPosition().y, paddle1Drawable.getPosition().y + paddle1Drawable.getSize().y));

            delete least;
            least = NULL;

        }

        least = ball.collides(paddle2Drawable);
        if (least != NULL) {

            ball.move(sf::Vector2f(least->x, least->y));
            ball.bounce(sf::Vector2f(least->x, least->y));
            ball.changeYVel(sf::Vector2f(paddle2Drawable.getPosition().y, paddle2Drawable.getPosition().y + paddle2Drawable.getSize().y));

            delete least;
            least = NULL;

        }

    }

}

void PlayState::handleInput() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        paddle1.setDirection(Paddle::UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        paddle1.setDirection(Paddle::DOWN);

    sf::RectangleShape paddle1Drawable = *dynamic_cast<const sf::RectangleShape *>(&(paddle1.getDrawable()));
    ball.handleInput();
    if (!ball.getMoveState() &&
        (ball.getDrawable().getPosition().x == paddle1Drawable.getPosition().x + paddle1Drawable.getSize().x) &&
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        ball.setMoveState(true);

    sf::RectangleShape paddle2Drawable = *dynamic_cast<const sf::RectangleShape *>(&(paddle2.getDrawable()));
    sf::CircleShape circle = *dynamic_cast<const sf::CircleShape *>(&(ball.getDrawable()));
    if (!ball.getMoveState() &&
        (ball.getDrawable().getPosition().x == paddle2Drawable.getPosition().x - circle.getRadius() * 2.0f) &&
        serveTimer >= SERVE_TIME) {

        serveTimer = 0.0f;
        ball.setMoveState(true);

    }
    //idea for clickables:
    //for (click in clickables)
    //    if (click.handleClick())
    //        break;

}
