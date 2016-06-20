#include "Team.h"

Team::Team(Config &config)
{
    this->config = config;
}

Team::~Team()
{
    //dtor
}

void Team::LoadTeam(int loadplayers, bool PlayerTeam, string kit)
{
    if(PlayerTeam && loadplayers > 0) loadplayers--;
    for(int i=0; i<loadplayers; i++)pTexture.push_back(sf::Texture());
    for(int i=0; i<loadplayers; i++)
    {
        Players.push_back(new Player());
        Players[i]->AddPlayer(true, this->config, pTexture[i], kit);
    }
}

void Team::RenderTeam(sf::RenderWindow &mWindow)
{
    for(size_t i=0; i<Players.size(); i++)
    {
        Players[i]->Render(mWindow);
    }
}

void Team::SetControllablePlayer(int player, bool bot)
{
    Players[player]->SetPlayerBot(bot);
}

void Team::AddPlayer(Player* player)
{
    Players.push_back(player);
}

void Team::UpdateTeam(sf::Time elapsedTime, sf::Sprite &mRink, float PlayerSpeed)
{
    size_t follow = -1;
    sf::Vector2f MyPos;
    sf::Vector2f FollowPos;
    for(size_t i=0; i<Players.size(); i++)
    {
        Players[i]->OnPlayerUpdate(elapsedTime, mRink, PlayerSpeed);
        if(!Players[i]->IsPlayerBot())
        {
            follow = i;
            FollowPos = Players[follow]->GetPlayerPos();
        }
    }
    for(size_t i=0; i<Players.size(); i++)
    {
        if(!Players[i]->IsPlayerBot())
        {
            follow = i;
            FollowPos = Players[follow]->GetPlayerPos();
        }
        else
        {
            if(follow != -1)
            {
                bool left = false, up = false, right = false, down = false, issprint = false;
                MyPos = Players[i]->GetPlayerPos();
                float fixposx = (-mRink.getPosition().x*2) - (mRink.getTexture()->getSize().x-config.GetResolution().x);
                float fixposy = (-mRink.getPosition().y*2) - (mRink.getTexture()->getSize().y-config.GetResolution().y);
                float fixexposx = (config.GetResolution().x-Players[follow]->GetPlayerSize().x)/2;
                float fixexposy = (config.GetResolution().y-Players[follow]->GetPlayerSize().y)/2;
                //if(FollowPos.x > 0.f && (-MyPos.x/30 < mRink.getTexture()->getSize().x) && (MyPos.x/30 - fixposx > -2.f || FollowPos.x - fixexposx < -2.f)) left = true;
                if(MyPos.x/30 - fixposx > -2.f || FollowPos.x - fixexposx < -2.f) left = true;
                if(MyPos.x/30 - fixposx < 2.f || FollowPos.x - fixexposx > 2.f) right = true;
                if(MyPos.y/30 - fixposy > -2.f || FollowPos.y - fixexposy < -2.f) up = true;
                if(MyPos.y/30 - fixposy < 2.f || FollowPos.y - fixexposy > 2.f) down = true;
                Players[i]->AIMove(left, up, right, down, issprint, elapsedTime, PlayerSpeed);
            }
        }
    }
}

Player* Team::GetPlayer(int id)
{
    return Players[id];
}

string Team::GetTeamName()
{
    return Name;
}
/*
if(MyPos.x/30 - fixposx < 2.f) right = true;
if(MyPos.x/30 - fixposx > -2.f || FollowPos.x - fixexposx < -2.f) left = true;
if(MyPos.x/30 - fixposx < 2.f || FollowPos.x - fixexposx > 2.f) right = true;
if(MyPos.y/30 - fixposy > -2.f || FollowPos.y - fixexposy < -2.f) up = true;
if(MyPos.y/30 - fixposy < 2.f || FollowPos.y - fixexposy > 2.f) down = true;
Players[i]->AIMove(left, up, right, down, issprint, elapsedTime, PlayerSpeed);
std::cout << -MyPos.x/30 << " " << mRink.getTexture()->getSize().x << std::endl;
*/
