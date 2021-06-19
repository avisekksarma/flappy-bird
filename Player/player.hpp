#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    ~Player();

private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
};

#endif