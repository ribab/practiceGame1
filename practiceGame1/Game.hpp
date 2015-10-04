#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class Game {

    public:
        static Game & getInst();
        
        void init(sf::Vector2i windowDimensions,
                  sf::String windowName);
        void pushState(GameState *state);
        void popState();
        GameState *peekState();

        void gameLoop();

        sf::RenderWindow & getWindow();

        ~Game();

    private:
        
        std::stack<GameState *> states;
        sf::RenderWindow window;

        Game() {};
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        bool paused = false;
};

#endif /* GAME_HPP */
