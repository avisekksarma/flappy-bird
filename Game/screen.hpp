#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <SFML/Graphics.hpp>

class Screen
{
public:
    Screen(const sf::Vector2u &windowSize, sf::RenderWindow &window, const std::string &fileName) : mWindowSize(windowSize), mWindow(window)
    {
        if (!mTexture.loadFromFile(fileName))
        {
            //error
            exit(0);
        }
        mSprite.setTexture(mTexture);
        mSprite.setOrigin(mTexture.getSize().x/2.0,mTexture.getSize().y/2.0);
        mSprite.setPosition(mWindowSize.x/2.0, mWindowSize.y/2.0);
        // mSprite.setScale(float(windowSize.x) / mTexture.getSize().x, float(windowSize.y) / mTexture.getSize().y);
    }
    ~Screen(){};

    void run()
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

protected:
    bool processEventsAndEndOnClick()
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
    
    virtual void render()
    {
        mWindow.clear(sf::Color::Cyan);
        mWindow.draw(mSprite);
        mWindow.display();
    }

protected:
    const sf::Vector2u mWindowSize;
    sf::RenderWindow &mWindow;
    sf::Texture mTexture;
    sf::Sprite mSprite;
};
// class definition/interface ends;

#endif