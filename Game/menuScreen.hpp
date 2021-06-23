#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP
#include <SFML/Graphics.hpp>

class MenuScreen
{
public:
    MenuScreen(const sf::Vector2u &windowSize, sf::RenderWindow &window);
    ~MenuScreen();

    void run();

private:
    bool processEventsAndEndOnClick();
    void render();

private:
    const sf::Vector2u mWindowSize;
    sf::RenderWindow &mWindow;
    sf::Texture mTexture;
    sf::Sprite mSprite;
};

#endif