#include "obstacle.hpp"
#include <iostream>

using namespace std;

Obstacle::Obstacle(const sf::Vector2u &windowSize):mWindowSize(windowSize)
{
    if (!mObsTexture[NINV].loadFromFile("./Assets/sprites/pipe-green.png"))
    {
        //error
        exit(0);
    }
    if (!mObsTexture[INV].loadFromFile("./Assets/sprites/pipe-green-inverted.png"))
    {
        //error
        exit(0);
    }

}

// make new obs after the genDuration
// move the obs by some moving speed.
void Obstacle::updateObs(float dt,float baseHeight)
{
    mCurrDuration += dt;
    if (mCurrDuration >= mGenDuration)
    {
        mCurrDuration = 0.0f;
        createNewObstacle(baseHeight);
    }
}

Obstacle::~Obstacle() {}

void Obstacle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(int i = 0;i < mObstacles.size();i++){
        target.draw(mObstacles[i][0],states);
        target.draw(mObstacles[i][1],states);
    }
}

void Obstacle::createNewObstacle(float baseHeight)
{
    std::vector<sf::Sprite> obs(2);
    // range for the height of obstacle.
    sf::Vector2f range1(mWindowSize.y / 2.0 + 20, mWindowSize.y / 2.0 + 50);
    sf::Vector2f range2(mWindowSize.y / 2.0 - 20, mWindowSize.y / 2.0 - 50);

    std::vector<sf::Vector2f> ranges{range1,range2};
    obs[0].setTexture(mObsTexture[NINV]);
    obs[1].setTexture(mObsTexture[INV]);

    obs[2].setOrigin(0,0);

    for (int i = 0; i < obs.size(); ++i)
    {
        //FIXME: 100 should be deleted.
        obs[i].setPosition(mWindowSize.x - 100, Random::get(ranges[i].x, ranges[i].y));
    }
    
    obs[1].setTextureRect(sf::IntRect(0, 0, mObsTexture[NINV].getSize().x, mWindowSize.y - obs[1].getPosition().y - baseHeight));

    // obs[2].setTextureRect(sf::IntRect(0, 0, mObsTexture.getSize().x, windowSize.y / 2.0 - delta));

    mObstacles.push_back(obs);
}

Obstacle::ObstacleType Obstacle::getObstacles() const
{
    return mObstacles;
}