#include "game.hpp"
#include <string>

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
        // code execution is here means user clicked in game over screen,
        // since in this version there is no restart feature, so we just 
        // end the game.
        mWindow.close();
        exit(0);
    }
}
void Game::render()
{
    mWindow.clear(sf::Color::Cyan);
    mWindow.draw(mBg);
    mWindow.draw(mBird.getSprite());
    mWindow.display();
}

void Game::Score::loadTextures()
{
    for (int i = 0; i < 10; i++)
    {
        textureMap[i] = sf::Texture();
        if (!textureMap[i].loadFromFile("./Assets/sprites/" + std::to_string(i) + ".png"))
        {
            //error
            std::cout << "Could not load the " << i << ".png score image" << std::endl;
        }
    }
    makeSprites();
}
void Game::Score::makeSprites()
{
    for (int i = 0; i < 10; i++)
    {
        spriteMap[i] = sf::Sprite();
        spriteMap[i].setTexture(textureMap[i]);
    }
}

void Game::Score::renderScore(sf::RenderWindow &window, const sf::Vector2u windowSize)
{
    int firstDigit, secondDigit;
    firstDigit = score / 10;
    secondDigit = score % 10;
    spriteMap[firstDigit].setPosition(float(windowSize.x) * 0.5, float(windowSize.x) * 0.15);
    spriteMap[secondDigit].setPosition(float(windowSize.x) * 0.5 + textureMap[firstDigit].getSize().x, float(windowSize.x) * 0.15);

    // render them
    window.draw(spriteMap[firstDigit]);
    window.draw(spriteMap[secondDigit]);
}

void Game::Score::increaseScore(){
    score++;
}