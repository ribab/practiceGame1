#ifndef TITLESTATE_HPP
#define TITLESTATE_HPP

#include <SFML/Graphics.hpp>

#include "Button.hpp"

#include "GameState.hpp"

class TitleState : public GameState {

    private:
        Button startButton;
        Button quitButton;

    public:
        TitleState();
        TitleState(const sf::RenderWindow &window);

        void init(const sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        void update(const sf::RenderWindow &window,
                    const sf::Time &tslu);
        void handleInput();

};

#endif
