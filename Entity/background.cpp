#include "background.hpp"
#include <iostream>
#include <utility>

Background::Background(const sf::Vector2u &windowSize)
    : mWindowSize(windowSize),
      mObs(windowSize)
{
    loadTextures();
    makeSprites();
    mCurrBGSprite = mSpriteMap[NIGHT_BG];
}

Background::~Background() {}

//FIXME: i think constantly making and destroying vector could be inefficient
//DEPRECATED
std::vector<sf::Sprite> Background::getBackground()
{
    std::vector<sf::Sprite> bg;
    bg.push_back(mCurrBGSprite);
    bg.push_back(mSpriteMap[BASE]);
    return bg;
}

void Background::loadTextures()
{
    mTextureMap.insert(std::make_pair(DAY_BG, sf::Texture()));
    mTextureMap.insert(std::make_pair(NIGHT_BG, sf::Texture()));
    mTextureMap.insert(std::make_pair(BASE, sf::Texture()));
    // mTextureMap.insert(std::make_pair(OBSTACLE, sf::Texture()));

    if (!mTextureMap[DAY_BG].loadFromFile(mFileNameMap[DAY_BG]))
    {
        // error loading the file.
        // The program should stop.
        std::cout << "Error loading the day bg texture." << std::endl;
        exit(0);
    }
    else
    {
        mTextureMap[DAY_BG].setSmooth(true);
    }

    if (!mTextureMap[NIGHT_BG].loadFromFile(mFileNameMap[NIGHT_BG]))
    {
        std::cout << "Error loading the night bg texture." << std::endl;
        exit(0);
    }
    else
    {
        mTextureMap[NIGHT_BG].setSmooth(true);
    }

    if (!mTextureMap[BASE].loadFromFile(mFileNameMap[BASE]))
    {
        std::cout << "Error loading the base bg texture." << std::endl;
        exit(0);
    }
    else
    {
        mTextureMap[BASE].setSmooth(true);
    }
}

void Background::makeSprites()
{
    mSpriteMap.insert(std::make_pair(DAY_BG, sf::Sprite()));
    mSpriteMap.insert(std::make_pair(NIGHT_BG, sf::Sprite()));
    mSpriteMap.insert(std::make_pair(BASE, sf::Sprite()));
    int count = 0;
    for (BGType bg[2] = {DAY_BG, NIGHT_BG}; count < 2; count++)
    {
        mSpriteMap[bg[count]].setTexture(mTextureMap[bg[count]]);
        mSpriteMap[bg[count]].setPosition(0, 0);
        mSpriteMap[bg[count]].setScale(float(mWindowSize.x) / mTextureMap[bg[count]].getSize().x, (float(mWindowSize.y) - mTextureMap[BASE].getSize().y) / mTextureMap[bg[count]].getSize().y);
    }

    mSpriteMap[BASE].setTexture(mTextureMap[BASE]);
    mSpriteMap[BASE].setPosition(0, mTextureMap[DAY_BG].getSize().y * mSpriteMap[DAY_BG].getScale().y);
    //FIXME: the 50 is a magic number in following two statements.
    mSpriteMap[BASE].setTextureRect(sf::IntRect(0, 0, 300, mTextureMap[BASE].getSize().y));
    mSpriteMap[BASE].setScale(2 * float(mWindowSize.x) / 300, 1.0f);
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSpriteMap.at(DAY_BG), states);
    target.draw(mObs, states);
    target.draw(mSpriteMap.at(BASE), states);
}

void Background::update(float dt)
{
    mObs.updateObs(dt, mTextureMap[BASE].getSize().y);
    mSpriteMap[BASE].move(-mBaseMovingSpeed * dt, 0);
    //TODO: a fake scrolling infitely part, i may change to standard practice later.
    if (mSpriteMap[BASE].getPosition().x <= float(mWindowSize.x) * (-1.0f))
    {
        mSpriteMap[BASE].setPosition(0, mTextureMap[DAY_BG].getSize().y * mSpriteMap[DAY_BG].getScale().y);
    }
}
