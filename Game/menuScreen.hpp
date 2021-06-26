#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP
#include <SFML/Graphics.hpp>
#include "screen.hpp"

class MenuScreen : public Screen
{
public:
    MenuScreen(const sf::Vector2u &windowSize, sf::RenderWindow &window) : Screen(windowSize, window, "./Assets/sprites/menuscreen.png") {}
    ~MenuScreen() {}
};

// class definition ends

#endif