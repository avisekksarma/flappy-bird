#include "game.hpp"
#include <string>

Game::Game() : mWindowSize(1000, 800), mWindow(sf::VideoMode(mWindowSize.x, mWindowSize.y), "Flappy-Bird"), mBg(mWindowSize), mBird(mWindowSize), mMenu(mWindowSize, mWindow), mOver(mWindowSize, mWindow) {}

Game::~Game() {}
void Game::run()
{
    if (mIsThisMenuScreen)
        mMenu.run();

    // code execution reaches here means the user is now in game,
    // i.e. clicked on menu screen.
    sf::Clock clock;
    mWindow.setFramerateLimit(60);
    mAudio.mBgMusic.play();
    mAudio.mBgMusic.setLoop(true);
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
    if (mBird.shouldScoreIncrease(mBg.getObs().getObstacles(), mBg.getTextures()[Background::BASE].getSize().y))
    {
        // user gets past a obstacle, i.e one more point.
        mAudio.mSound[AudioManager::POINT].play();
        mScore.increaseScore();
    }

    if (mBird.hasBirdCollided(mBg.getObs().getObstacles(), mBg.getTextures()[Background::BASE].getSize().y))
    {
        mAudio.mSound[AudioManager::HIT].play();
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
    mScore.renderScore(mWindow, mWindowSize);
    mWindow.display();
}

Game::Score::Score()
{
    // loads the textures, this function also calls the makesprites func.
    loadTextures();
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
    sf::Sprite s1, s2;
    int firstDigit, secondDigit;
    firstDigit = score / 10;
    secondDigit = score % 10;
    s1 = spriteMap[firstDigit];
    s1.setPosition(float(windowSize.x) * 0.5, float(windowSize.x) * 0.15);
    s2 = spriteMap[secondDigit];
    s2.setPosition(float(windowSize.x) * 0.5 + textureMap[firstDigit].getSize().x, float(windowSize.x) * 0.15);

    // render them
    window.draw(s1);
    window.draw(s2);
}

void Game::Score::increaseScore()
{
    score++;
}