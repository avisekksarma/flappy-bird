#include "game.hpp"

Game::Game() : mWindowSize(1000, 800), mWindow(sf::VideoMode(mWindowSize.x, mWindowSize.y), "Flappy-Bird"), mBg(mWindowSize), mBird(mWindowSize), mMenu(mWindowSize, mWindow), mOver(mWindowSize, mWindow) {}

Game::~Game() {}
void Game::run()
{
    if (mIsThisMenuScreen)
        mMenu.run();
    sf::Clock clock;
    while (mWindow.isOpen())
    {
        processEvents();
        sf::Time dt = clock.restart();
        update(dt.asSeconds());
        render();
    }
}

void Game::processEvents()
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
                mBird.handleInput();
            }
        }
    }
}

void Game::update(float dt)
{
    mBg.update(dt);
    mBird.update(dt, mBg.getObs().getObstacles(), mBg.getTextures()[Background::BASE].getSize().y);
    if (mBird.hasBirdCollided(mBg.getObs().getObstacles(), mBg.getTextures()[Background::BASE].getSize().y))
    {
        mOver.run();
    }
}
void Game::render()
{
    mWindow.clear(sf::Color::Cyan);
    mWindow.draw(mBg);
    mWindow.draw(mBird.getSprite());
    mWindow.display();
}
