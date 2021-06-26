#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../Entity/background.hpp"
#include "../Player/player.hpp"
#include "menuScreen.hpp"
#include "gameOverScreen.hpp"

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
    bool mIsThisMenuScreen = true;
    MenuScreen mMenu;
    GameOverScreen mOver;
    Background mBg;
    Player mBird;

public:
    sf::RenderWindow mWindow;
};

#endif