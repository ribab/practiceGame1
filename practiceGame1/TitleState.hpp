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

        void init();
        void draw();
        void update(const sf::Time &tslu);
        void handleInput();

};

#endif
