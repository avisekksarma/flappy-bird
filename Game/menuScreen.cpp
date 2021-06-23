#include "menuScreen.hpp"

MenuScreen::MenuScreen(const sf::Vector2u &windowSize, sf::RenderWindow &window) : mWindowSize(windowSize), mWindow(window)
{
    if (!mTexture.loadFromFile("./Assets/sprites/menuscreen.png"))
    {
        //error
        exit(0);
    }
    mSprite.setTexture(mTexture);
    mSprite.setPosition(0, 0);
    mSprite.setScale(float(windowSize.x) / mTexture.getSize().x, float(windowSize.y) / mTexture.getSize().y);
}
MenuScreen::~MenuScreen() {}

void MenuScreen::run()
{
    sf::Clock clock;
    while (mWindow.isOpen())
    {
        if (processEventsAndEndOnClick())
        {
            break;
        };
        render();
    }
}

bool MenuScreen::processEventsAndEndOnClick()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // end the menu screen and go to game screen
                return true;
            }
        }
    }
    return false;
}

void MenuScreen::render()
{
    mWindow.clear(sf::Color::Cyan);
    mWindow.draw(mSprite);
    mWindow.display();
}
