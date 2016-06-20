#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include "Player.h"
#include "Config.h"
#include "string"

using namespace std;

class Team
{
    public:
        Team(Config &config);
        virtual ~Team();
        void LoadTeam(int loadplayers, bool PlayerTeam, string kit);
        void RenderTeam(sf::RenderWindow &mWindow);
        void SetControllablePlayer(int player, bool bot);
        void AddPlayer(Player* player);
        void UpdateTeam(sf::Time elapsedTime, sf::Sprite &mRink, float PlayerSpeed);
        Player* GetPlayer(int id);
        string GetTeamName();
    protected:
    private:
        Config config;
        std::vector <sf::Texture> pTexture;
        std::vector <Player*> Players;
        string Name;
};

#endif // TEAM_H
