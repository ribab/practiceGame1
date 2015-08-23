#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class Game {

    public:
        Game();
        Game(sf::RenderWindow &window);
        ~Game();

        void pushState(GameState *state);
        void popState();
        GameState *peekState();

        void gameLoop(sf::RenderWindow &window);

    private:
        std::stack<GameState *> states;
        sf::RenderWindow window;
};

#endif /* GAME_HPP */
