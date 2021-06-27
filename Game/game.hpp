#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "../Entity/background.hpp"
#include "../Player/player.hpp"
#include "menuScreen.hpp"
#include "gameOverScreen.hpp"
#include "../Entity/audioManager.hpp"


class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

private:
    const sf::Vector2u mWindowSize;
    bool mIsThisMenuScreen = true;
    MenuScreen mMenu;
    GameOverScreen mOver;
    Background mBg;
    Player mBird;
    AudioManager mAudio;
    // everything about score
    struct Score
    {
    public:
        int score = 0;
        std::map<int, sf::Texture> textureMap;
        std::map<int, sf::Sprite> spriteMap;

    public:
        Score();
        // increase the score when shouldScoreIncrease of player class returns true
        void increaseScore();
        void renderScore(sf::RenderWindow &window, const sf::Vector2u windowSize);

    private:
        void loadTextures();
        void makeSprites();
    };

public:
    sf::RenderWindow mWindow;
    Score mScore;
};

#endif
