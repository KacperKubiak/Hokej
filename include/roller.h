#ifndef ROLLER_H
#define ROLLER_H

#include <SFML/Graphics.hpp>
#include "Config.h"
#include <iostream>
#include <vector>
#include "Player.h"

class roller
{
    public:
        roller();
        void AddRoller(Config &config);
        void Render(sf::RenderWindow &mWindow);
        void Update(sf::Time elapsedTime, sf::Sprite &mRink);
        sf::Vector2f GetRollerPos();
        sf::Vector2f GetVirtualRollerPos(sf::Sprite &mRink);
        virtual ~roller();
        void AttachRollerToPlayer(bool attach, Player* Players);
        void ShootTo(sf::Vector2f Target, int slong);
    protected:
    private:
        sf::Sprite sRoller;
        sf::Texture rTexture;
        sf::Vector2f VirtualPos;
        sf::Vector2f ShotTarget;
        int shotlong;
        bool IsAttached;
        Player* AttachToPlayer;
};

#endif // ROLLER_H
