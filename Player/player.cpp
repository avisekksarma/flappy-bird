#include "player.hpp"
#include <iostream>

using namespace std;

Player::Player(const sf::Vector2u &windowSize) : mWindowSize(windowSize), mSizePerFrame(34.0f, 24.0f)
{
    if (!mTexture.loadFromFile("./Assets/sprites/yellowbird.png"))
    {
        //error
        exit(0);
    }

    mSprite.setTexture(mTexture);
    // initial setup
    mSprite.setOrigin(mTexture.getSize().x/2.0,mTexture.getSize().y/2.0);
    mSprite.setTextureRect(sf::IntRect(0, 0, mSizePerFrame.x, mSizePerFrame.y));
    mSprite.setPosition(sf::Vector2f(Random::get(float(mWindowSize.x) * 0.3f, float(mWindowSize.x) * 0.35f), mWindowSize.y / 2.0));
    mSprite.setScale(1.3f, 1.3f);
}
Player::~Player() {}

void Player::update(float dt, const Obstacle::ObstacleType &obs, float baseHeight)
{
    // animation part starts
    mCurrDuration += dt;
    if (mCurrDuration >= mAnimDuration)
    {
        mCurrDuration = 0.0f;
        mCurrentFrame = mCurrentFrame + mDirn;
        if (mCurrentFrame > 2)
        {
            mCurrentFrame = 1;
            mDirn = Player::LEFT;
        }
        else if (mCurrentFrame < 0)
        {
            mCurrentFrame = 1;
            mDirn = Player::RIGHT;
        }
        mSprite.setTextureRect(sf::IntRect(mCurrentFrame * mSizePerFrame.x, 0, mSizePerFrame.x, mSizePerFrame.y));
    }
    // animation part ends

    // jumping and falling part starts
    if (mSprite.getPosition().y <= mFinalUpperPos)
    {
        mVelocity = -mVelocity;
    }
    else
    {
        mVelocity = mVelocity + mAccln * dt;
    }

    mSprite.move(0, mVelocity * dt);
    // jumping and falling part ends

    // rotation part when it falls downwards
    if (mVelocity >= 0)
    {
        //TODO: magic number place
        mSprite.rotate(60 * dt);
        
    }
    else if (mVelocity < 0)
    {
        mSprite.setRotation(0);
    }
    // rotation part ends
}

sf::Sprite Player::getSprite() const
{
    return mSprite;
}
// obviously input is just click or up arrow
void Player::handleInput()
{
    mPosWhenClicked = mSprite.getPosition().y;
    //TODO: magic number place
    mFinalUpperPos = mPosWhenClicked - mJumpingHeight;
    //TODO: magic number place
    mVelocity = -250.0f;
}

bool Player::hasBirdCollided(const Obstacle::ObstacleType &obs, float baseHeight)
{
    for (int i = 0; i < obs.size(); ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (obs[i][j].sprite.getGlobalBounds().intersects(this->getSprite().getGlobalBounds()))
            {
                return true;
            }
        }
    }
    if (this->getSprite().getPosition().y + getSprite().getGlobalBounds().height > mWindowSize.y - baseHeight)
    {
        return true;
    }
    if (this->getSprite().getPosition().y < 0)
    {
        return true;
    }
    return false;
}

// returns true if bird gets past a new obstacle.
bool Player::shouldScoreIncrease(Obstacle::ObstacleType &obs, float baseHeight)
{
    for (int i = 0; i < obs.size(); ++i)
    {
        if (obs[i][0].pos == Obstacle::Pipe::RIGHT && mSprite.getPosition().x > obs[i][0].sprite.getPosition().x)
        {
            if (!hasBirdCollided(obs, baseHeight))
            {
                // now make that pipe as left pipe so that rechecking with
                // same pipe does not occur.
                obs[i][0].pos = Obstacle::Pipe::LEFT;
                // score should increase
                return true;
            }
        }
    }
    return false;
}