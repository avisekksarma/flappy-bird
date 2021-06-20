#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <vector>

// Manages everything related to background.
class Background:public sf::Drawable
{
public:
    Background(const sf::Vector2u &mWindowSize);
    ~Background();
    // DEPRECATED
    std::vector<sf::Sprite> getBackground();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    enum BGType{
        DAY_BG,NIGHT_BG,BASE,OBSTACLE
    };


private:
    void loadTextures();
    void makeSprites(const sf::Vector2u &mWindowSize);
    

private:
    std::map<BGType,std::string> mFileNameMap = {{DAY_BG,"./Assets/sprites/background-day.png"}, {NIGHT_BG,"./Assets/sprites/background-night.png"},{BASE,"./Assets/sprites/base.png"},{OBSTACLE,"./Assets/sprites/pipe-green.png"}};
    
    sf::Sprite mCurrBGSprite; // either day or night
    std::map<BGType,sf::Texture> mTextureMap;
    std::map<BGType,sf::Sprite> mSpriteMap;

    // obstacle part
    // std::vector<
};

#endif
