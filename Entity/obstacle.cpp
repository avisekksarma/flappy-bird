#include "obstacle.hpp"
#include <iostream>

using namespace std;

Obstacle::Obstacle(const sf::Vector2u &windowSize) : mWindowSize(windowSize)
{
    if (!mObsTextureMap[NINV].loadFromFile("./Assets/sprites/pipe-green.png"))
    {
        //error
        exit(0);
    }
    if (!mObsTextureMap[INV].loadFromFile("./Assets/sprites/pipe-green-inverted.png"))
    {
        //error
        exit(0);
    }
    cout << "obstacle.cpp - here" << endl;
}

// make new obs after the genDuration
// move the obs by some moving speed.
void Obstacle::updateObs(float dt, float baseHeight)
{
    mCurrDuration += dt;

    // new obstacles making part.
    if (mIsThisInitialTime && mCurrDuration >= mInitialWaitingTime)
    {
        // now after this part, the initial obstacle is made,
        // so initial part = false;
        mIsThisInitialTime = false;
        mCurrDuration = 0.0f;
        createNewObstacle(baseHeight);
    }
    if (!mIsThisInitialTime && mCurrDuration >= mGenDuration)
    {
        mCurrDuration = 0.0f;
        createNewObstacle(baseHeight);
    }
    // new obstacle making part ends.

    // update the position of obstacles or delete if out of screen
    for (int i = 0; i < mObstacles.size(); i++)
    {
        if (mObstacles[i][0].sprite.getPosition().x + mObsTextureMap[NINV].getSize().x * mObstacles[i][0].sprite.getScale().x <= 0)
        {
            // case when obstacle goes out of screen after moving
            mObstacles.erase(mObstacles.begin() + i);
        }
        else
        {
            mObstacles[i][0].sprite.move(-mSpeed * dt, 0.0f);
            mObstacles[i][1].sprite.move(-mSpeed * dt, 0.0f);
        }
    }

    // DIFFICULTY INCREASING ZONE.
    mGenDuration -= mGenDuration * 3 * dt;
    mSpeed += mSpeed * 5 * dt;
    
}

Obstacle::~Obstacle() {}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < mObstacles.size(); i++)
    {
        target.draw(mObstacles[i][0].sprite, states);
        target.draw(mObstacles[i][1].sprite, states);
    }
}

void Obstacle::createNewObstacle(float baseHeight)
{
    // 0 = non-inverted, 1 = inverted.
    std::vector<Obstacle::Pipe> obs(2);
    // range for the height of obstacle.
    sf::Vector2f range1(mWindowSize.y / 2.0 + 80, mWindowSize.y / 2.0 + 180);
    sf::Vector2f range2(mWindowSize.y / 2.0 - 80, mWindowSize.y / 2.0 - 180);

    std::vector<sf::Vector2f> ranges{range1, range2};
    obs[0].sprite.setTexture(mObsTextureMap[NINV]);
    obs[1].sprite.setTexture(mObsTextureMap[INV]);
    obs[1].sprite.setOrigin(0, mObsTextureMap[INV].getSize().y);

    for (int i = 0; i < obs.size(); ++i)
    {
        obs[i].sprite.setPosition(mWindowSize.x, Random::get(ranges[i].x, ranges[i].y));
        obs[i].sprite.setScale(2.0f, 1.0f);
    }
    //randomly overriding the position of one of the pipes by fixing other
    // just a block scope made

    int num = Random::get({0, 1});
    if (num == 1)
    {
        // overriding the inverted pipe position to be according to the pipe height
        obs[1].sprite.setPosition(mWindowSize.x, obs[0].sprite.getPosition().y - pipeHeight);

        if (obs[1].sprite.getPosition().y > mObsTextureMap[INV].getSize().y)
        {
            // scale inverted pipe in the y direction so that the upper part is not
            // shown empty as the pipe is lower in position than its size
            obs[1].sprite.scale(1.0f, obs[1].sprite.getPosition().y / mObsTextureMap[INV].getSize().y);
        }
    }
    else
    {
        // overriding the non-inverted pipe position to be according to the pipe height
        obs[0].sprite.setPosition(mWindowSize.x, obs[1].sprite.getPosition().y + pipeHeight);
        if (mWindowSize.y - obs[0].sprite.getPosition().y > mObsTextureMap[NINV].getSize().y + baseHeight)
        {
            // scale inverted pipe in the y direction so that the upper part is not
            // shown empty as the pipe is lower in position than its size
            obs[0].sprite.scale(1.0f, (mWindowSize.y - obs[0].sprite.getPosition().y - baseHeight) / mObsTextureMap[NINV].getSize().y);
        }
    }

    // obs[0].sprite.setTextureRect(sf::IntRect(0, 0, mObsTextureMap[NINV].getSize().x, mWindowSize.y - obs[0].sprite.getPosition().y - baseHeight));

    mObstacles.push_back(obs);
}

Obstacle::ObstacleType &Obstacle::getObstacles()
{
    return mObstacles;
}