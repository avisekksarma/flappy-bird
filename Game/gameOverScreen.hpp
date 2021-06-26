#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP
#include <SFML/Graphics.hpp>
#include "screen.hpp"

class GameOverScreen : public Screen
{
public:
    GameOverScreen(const sf::Vector2u &windowSize, sf::RenderWindow &window) : Screen(windowSize, window, "./Assets/sprites/gameover.png") {
        if(!mPlayAgainTexture.loadFromFile("./Assets/sprites/menuscreen.png")){
            //error
            exit(0);
        }
        mPlayAgainSprite.setTexture(mPlayAgainTexture);
        mPlayAgainSprite.setTextureRect(sf::IntRect(0,204,184,63));
        mPlayAgainSprite.setOrigin(184/2.0,63/2.0);
        mPlayAgainSprite.setPosition(mWindowSize.x/2.0,mWindowSize.y/2.0 + 100);
    }
    ~GameOverScreen() {}

    void render()
    {
        mWindow.clear(sf::Color::Cyan);
        mWindow.draw(mSprite);
        mWindow.draw(mPlayAgainSprite);
        mWindow.display();
    }

private:
    sf::Texture mPlayAgainTexture;
    sf::Sprite mPlayAgainSprite;
};

// class definition ends

#endif