#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <map>
#include <SFML/Audio.hpp>

class AudioManager
{
public:
    AudioManager()
    {
        mSoundBuffer[POINT] = sf::SoundBuffer();
        mSoundBuffer[HIT] = sf::SoundBuffer();
        mSoundBuffer[FLY] = sf::SoundBuffer();
        if (!mSoundBuffer[POINT].loadFromFile("./Assets/audio/point.wav"))
        {
            //error
            exit(0);
        }
        else
        {
            mSound[POINT] = sf::Sound();
            mSound[POINT].setBuffer(mSoundBuffer[POINT]);
        }
        if (!mSoundBuffer[HIT].loadFromFile("./Assets/audio/hit.wav"))
        {
            //error
            exit(0);
        }
        else
        {
            mSound[HIT] = sf::Sound();
            mSound[HIT].setBuffer(mSoundBuffer[HIT]);
        }
        if (!mSoundBuffer[FLY].loadFromFile("./Assets/audio/wing.wav"))
        {
            //error
            exit(0);
        }
        else
        {
            mSound[FLY] = sf::Sound();
            mSound[FLY].setBuffer(mSoundBuffer[FLY]);
        }

        if (!mBgMusic.openFromFile("./Assets/audio/bg-music.wav"))
           {
               exit(0);
           }
    }

public:
    enum SoundType
    {
        // one point/score gain sound
        POINT,
        HIT,
        FLY
    };
    std::map<AudioManager::SoundType, sf::Sound> mSound;
    sf::Music mBgMusic;

private:
    std::map<AudioManager::SoundType, sf::SoundBuffer> mSoundBuffer;
};

#endif