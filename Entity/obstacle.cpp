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
        if (mObstacles[i][0].getPosition().x + mObsTextureMap[NINV].getSize().x * mObstacles[i][0].getScale().x  <= 0)
        {
            // case when obstacle goes out of screen after moving
            mObstacles.erase(mObstacles.begin() + i);
        }
        else
        {
            mObstacles[i][0].move(-mSpeed * dt, 0.0f);
            mObstacles[i][1].move(-mSpeed * dt, 0.0f);
        }
    }
}

Obstacle::~Obstacle() {}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < mObstacles.size(); i++)
    {
        target.draw(mObstacles[i][0], states);
        target.draw(mObstacles[i][1], states);
    }
}

void Obstacle::createNewObstacle(float baseHeight)
{
    // 0 = non-inverted, 1 = inverted.
    std::vector<sf::Sprite> obs(2);
    // range for the height of obstacle.
    sf::Vector2f range1(mWindowSize.y / 2.0 + 80, mWindowSize.y / 2.0 + 180);
    sf::Vector2f range2(mWindowSize.y / 2.0 - 80, mWindowSize.y / 2.0 - 180);

    std::vector<sf::Vector2f> ranges{range1, range2};
    obs[0].setTexture(mObsTextureMap[NINV]);
    obs[1].setTexture(mObsTextureMap[INV]);

    obs[1].setOrigin(0, mObsTextureMap[INV].getSize().y);

    for (int i = 0; i < obs.size(); ++i)
    {
        //FIXME: 100 should be deleted.
        obs[i].setPosition(mWindowSize.x, Random::get(ranges[i].x, ranges[i].y));
        obs[i].setScale(2.0f, 1.0f);
    }

    obs[0].setTextureRect(sf::IntRect(0, 0, mObsTextureMap[NINV].getSize().x, mWindowSize.y - obs[0].getPosition().y - baseHeight));

    // obs[2].setTextureRect(sf::IntRect(0, 0, mObsTexture.getSize().x, windowSize.y / 2.0 - delta));

    mObstacles.push_back(obs);
}

Obstacle::ObstacleType Obstacle::getObstacles() const
{
    return mObstacles;
}