#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>
#include "obstacle.hpp"

// Manages everything related to background.
class Background : public sf::Drawable
{
public:
    enum BGType
    {
        DAY_BG,
        NIGHT_BG,
        BASE
    };

public:
    Background(const sf::Vector2u &windowSize);
    ~Background();
    // DEPRECATED
    std::vector<sf::Sprite> getBackground();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(float dt);

    Obstacle& getObs()
    {
        return mObs;
    }

    std::map<BGType, sf::Texture> getTextures() const
    {
        return mTextureMap;
    }

private:
    // private member funcs
    void loadTextures();
    void makeSprites();

private:
    // private data members
    std::map<BGType, std::string> mFileNameMap = {{DAY_BG, "./Assets/sprites/background-day.png"}, {NIGHT_BG, "./Assets/sprites/background-night.png"}, {BASE, "./Assets/sprites/base.png"}};

    sf::Sprite mCurrBGSprite; // either day or night
    std::map<BGType, sf::Texture> mTextureMap;
    std::map<BGType, sf::Sprite> mSpriteMap;

    const sf::Vector2u &mWindowSize;
    float mBaseMovingSpeed = 100.0f; // i.e 80px/seconds

    Obstacle mObs;
};

#endif
