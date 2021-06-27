#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "../randomLib/random.hpp"
#include "../Entity/obstacle.hpp"

using Random = effolkronium::random_static;

class Player
{
public:
    Player(const sf::Vector2u &windowSize);
    ~Player();
    void update(float dt,const Obstacle::ObstacleType & obs,float baseHeight);
    void handleInput();

    sf::Sprite getSprite() const;

    bool hasBirdCollided(const Obstacle::ObstacleType & obs,float baseHeight);
    bool shouldScoreIncrease(Obstacle::ObstacleType & obs,float baseHeight);

private:
    enum Position
    {
        DOWN,
        MID,
        UP
    };
    enum FrameChangeDirn
    {
        LEFT = -1,
        RIGHT = 1
    };
    sf::Texture mTexture;
    sf::Sprite mSprite;
    const sf::Vector2u &mWindowSize;

    //animation data members
    const float mAnimDuration = 0.05f; // time(secs) before showing another frame.
    float mCurrDuration = 0.0f;
    const int mFrameCount = 3;
    int mCurrentFrame = 0; // 0,1,2,1,0,1,2 is the pattern of changing this.
    Player::FrameChangeDirn mDirn = Player::RIGHT;
    sf::Vector2f mSizePerFrame;

    // jumping and falling part
    float mVelocity = 100.0f;
    float mAccln = 130.0f;
    // position of the bird ( in y only ) when clicked;
    float PosWhenClicked;
    float finalUpperPos;
};

#endif
