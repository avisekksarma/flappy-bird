#include "player.hpp"

Player::Player(const sf::Vector2u &windowSize) : mWindowSize(windowSize), mSizePerFrame(34.0f, 24.0f)
{
    if (!mTexture.loadFromFile("./Assets/sprites/yellowbird.png"))
    {
        //error
        exit(0);
    }

    mSprite.setTexture(mTexture);
    // initial setup
    mSprite.setTextureRect(sf::IntRect(0, 0, mSizePerFrame.x, mSizePerFrame.y));
    mSprite.setPosition(sf::Vector2f(Random::get(float(mWindowSize.x) * 0.1f, float(mWindowSize.x) * 0.3f), mWindowSize.y / 2.0));
    mSprite.setScale(1.3f,1.3f);
}
Player::~Player() {}

void Player::update(float dt)
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
}

sf::Sprite Player::getSprite() const
{
    return mSprite;
}