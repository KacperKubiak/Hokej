#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Config.h"
#include "HUD.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Player
{
    public:
        Player();
        virtual ~Player();
        void AddPlayer(bool isbot, Config &config, sf::Texture &pTexture, string kit);
        void OnPlayerKeyStateChange(sf::Keyboard::Key key, bool isPressed);
        void OnPlayerUpdate(sf::Time elapsedTime, sf::Sprite &mRink, float PlayerSpeed);
        void Render(sf::RenderWindow &mWindow);
        sf::Vector2f GetPlayerPos();
        sf::Vector2f GetVirtualPlayerPos();
        sf::Vector2u GetPlayerSize();
        bool IsPlayerBot();
        void SetPlayerBot(bool bot);
        void AIMove(bool left, bool up, bool right, bool down, bool sprint, sf::Time elapsedTime, float PlayerSpeed);
        std::string GetPlayerName();
        bool GetPlayerHoldingBall();
        void SetPlayerHoldingBall(bool holding);
        bool IsPlayerShoot();
        float GetPlayerShootRot();
    protected:
    private:
        int id;
        bool pAI;
        sf::Sprite pPlayer;
        sf::Texture pTexture;
        sf::Sprite aSprite;//Arrow
        sf::Texture aTexture;//Arrow
        Config config;
        bool pIsMovingUp;
		bool pIsMovingDown;
		bool pIsMovingRight;
		bool pIsMovingLeft;
		bool pIsMovingSprint;
		bool pIsMovingShoot;
		sf::Vector2f RealPos;
		sf::Vector2f VirutalPos;
		float ShotRot;
		float ShotPower;
		bool pIsHoldingBall;
		std::string pName;
		float stamina;
		float power;
		HUD pHud;
};

#endif // PLAYER_H
