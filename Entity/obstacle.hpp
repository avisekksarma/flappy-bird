#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include "../randomLib/random.hpp"

using Random = effolkronium::random_static;

class Obstacle : public sf::Drawable
{
public:
    struct Pipe
    {
        sf::Sprite sprite;
        // the position to the bird
        enum Position
        {
            LEFT,
            RIGHT
        };
        Position pos = Pipe::RIGHT;
    };
    typedef std::vector<std::vector<Pipe>> ObstacleType;

    Obstacle(const sf::Vector2u &windowSize);
    ~Obstacle();
    // updates position of obstacle &
    // makes new obstacle &
    // deletes obstacles out of screen
    void updateObs(float dt, float baseHeight);

    ObstacleType & getObstacles();

private:
    void createNewObstacle(float baseHeight);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    // data storage part
    // ninv = non-inverted, inv = inverted
    enum PipeType
    {
        NINV,
        INV
    };
    std::map<Obstacle::PipeType, sf::Texture> mObsTextureMap = {
        {Obstacle::NINV, sf::Texture()},
        {Obstacle::INV, sf::Texture()}};

    // collection of all the obstacles shown in screen
    ObstacleType mObstacles;

    // logic part
    bool mIsThisInitialTime = true;
    const float mInitialWaitingTime = 3.0f; // 3 seconds
    float mGenDuration = 2.8f;              // 2 seconds initially, this will   change
    float mSpeed = 150.0f;                  // i.e 70px/seconds of velocity/speed.
    float mCurrDuration = 0.0f;
    const float pipeHeight = 170.0f;

    // other essential data
    const sf::Vector2u &mWindowSize;
    float baseHeight;
};

#endif
