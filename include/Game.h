#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Config.h"
#include "Team.h"
#include "Player.h"
#include "roller.h"

class Game
{
    public:
        Game();
        void Run(sf::RenderWindow &mWindow, Config &config);
		void processEvents(sf::RenderWindow &mWindow);
		void render(sf::RenderWindow &mWindow);
		void update(sf::Time elapsedTime);
		sf::Vector2f GetRinkPosition();
    protected:
    private:
        float PlayerSpeed;
        sf::Time TimePerFrame;
        sf::Sprite mRink;
        sf::Font mFont;
        sf::Texture	mField;
        int PlayersPerTeam;
        Config config;
        Player* MyPlayer;
        sf::Texture newtexture;
        Player newplayer;
        Team* Team1;
        Team* Team2;
        roller* Roller;
};

#endif // GAME_H
