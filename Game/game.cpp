#include "game.hpp"

Game::Game() : mWindowSize(1000, 800), mWindow(sf::VideoMode(mWindowSize.x, mWindowSize.y), "Flappy-Bird"),mBg(mWindowSize){}
Game::~Game() {}
void Game::run()
{
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
            mWindow.close();
    }
}
void Game::update(float dt) {}
void Game::render()
{
    mWindow.clear(sf::Color::Cyan);
    std::vector<sf::Sprite> bg = mBg.getBackground();
    for (int i = 0;i<bg.size();i++){
        mWindow.draw(bg[i]);
    }
    mWindow.display();
}
