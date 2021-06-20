#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../Entity/background.hpp"

// TODO: Idk of best design practice much esp. in sfml,
// but definitely i will follow oop : four pillars

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

private:
    const sf::Vector2u mWindowSize;
    sf::RenderWindow mWindow;
    Background mBg;

};

#endif