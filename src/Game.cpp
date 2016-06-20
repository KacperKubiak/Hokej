#include "Game.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

Game::Game()
{
    PlayersPerTeam = 2;
}

void Game::Run(sf::RenderWindow &mWindow, Config &config)
{
    this->config = config;
    if (mField.loadFromFile("Media/Textures/Rink.png"))
	{
        mRink.setTexture(mField);
        float centerx, centery;
        centerx = (mField.getSize().x - config.GetResolution().x)/2;
        centery = (mField.getSize().y - config.GetResolution().y)/2;
        mRink.setPosition(-centerx, -centery);
	}
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
    PlayerSpeed = 100.f;
    TimePerFrame = sf::seconds(1.f/60.f);

    string kit1 = "Media/Textures/player1.png";
    string kit2 = "Media/Textures/player2.png";
    Team1 = new Team(config);
    Team2 = new Team(config);
    Team1->LoadTeam(PlayersPerTeam, true, kit1);
    Team2->LoadTeam(PlayersPerTeam, false, kit2);

    newplayer.AddPlayer(false, config, newtexture, kit1);
    Team1->AddPlayer(&newplayer);

    Roller = new roller();
    Roller->AddRoller(config);

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents(mWindow);
			update(TimePerFrame);
		}
		render(mWindow);
	}
}

void Game::processEvents(sf::RenderWindow &mWindow)
{
    sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape) mWindow.close();
				newplayer.OnPlayerKeyStateChange(event.key.code, true);
				break;
            case sf::Event::KeyReleased:
				newplayer.OnPlayerKeyStateChange(event.key.code, false);
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Game::render(sf::RenderWindow &mWindow)
{
    mWindow.clear();
    mWindow.draw(mRink);
    Team1->RenderTeam(mWindow);
    Team2->RenderTeam(mWindow);
    newplayer.Render(mWindow);
    Roller->Render(mWindow);
	mWindow.display();
}

void Game::update(sf::Time elapsedTime)
{
    Team1->UpdateTeam(elapsedTime, mRink, PlayerSpeed);
    Team2->UpdateTeam(elapsedTime, mRink, PlayerSpeed);
    newplayer.OnPlayerUpdate(elapsedTime, mRink, PlayerSpeed);
    Roller->Update(elapsedTime, mRink);
    sf::Vector2f RollerPos = Roller->GetRollerPos();
    sf::Vector2f VRollerPos = Roller->GetVirtualRollerPos(mRink);
    sf::Vector2f PlayerPos = newplayer.GetPlayerPos();
    sf::Vector2f VPlayerPos = newplayer.GetVirtualPlayerPos();
    if(VRollerPos.x >= -3000 && VRollerPos.x <= 2800 && VRollerPos.y >= 58700 && VRollerPos.y <= 61700) cout << "GOOOOL!" << endl;
    if(VRollerPos.x >= -3400 && VRollerPos.x <= 2200 && VRollerPos.y <= -59900 && VRollerPos.y >= -62300) cout << "GOOOOL!" << endl;
    //Dolny lewy -3000 58700 dolny prawy 2800 58700
    //Górny lewy -3400 -59900 Górny prawy  2200 -59900
    //-62300
    for(int i=0; i<2; i++)
    {
        Team* TempTeam;
        if(i == 0) TempTeam = Team1;
        else TempTeam = Team2;

        int TempPlayers = PlayersPerTeam;
        if(PlayersPerTeam == 0) TempPlayers = 1;
        for(int i=0; i<TempPlayers; i++)
        {
            sf::Vector2f difference;
            difference.x = sqrt(pow(TempTeam->GetPlayer(i)->GetVirtualPlayerPos().x - VRollerPos.x, 2))/30;
            difference.y = sqrt(pow(TempTeam->GetPlayer(i)->GetVirtualPlayerPos().y - VRollerPos.y, 2))/30;
            if(difference.x < 100.f && difference.x > 40.f && difference.y <= 80.f && difference.y >= 40.f)
            {
                if(!TempTeam->GetPlayer(i)->GetPlayerHoldingBall() && !TempTeam->GetPlayer(i)->IsPlayerShoot())
                {
                    TempTeam->GetPlayer(i)->SetPlayerHoldingBall(true);
                    Roller->AttachRollerToPlayer(true, TempTeam->GetPlayer(i));
                }
                else if(TempTeam->GetPlayer(i)->IsPlayerShoot())
                {
                    TempTeam->GetPlayer(i)->SetPlayerHoldingBall(false);
                    Roller->AttachRollerToPlayer(false, TempTeam->GetPlayer(i));
                    sf::Vector2f Target(0.f, 0.f);
                    //x
                    if((TempTeam->GetPlayer(i)->GetPlayerShootRot() - 180)/90.0 >= -1 && (TempTeam->GetPlayer(i)->GetPlayerShootRot() - 180)/90.0 <= 1) Target.x = (TempTeam->GetPlayer(i)->GetPlayerShootRot() - 180)/90.0 * -1000.f;
                    else if(TempTeam->GetPlayer(i)->GetPlayerShootRot()/90.0 > 1) Target.x = (TempTeam->GetPlayer(i)->GetPlayerShootRot()/90.0-4)*1000;
                    else  Target.x = TempTeam->GetPlayer(i)->GetPlayerShootRot()/90.0 * 1000.f;
                    //y
                    if((TempTeam->GetPlayer(i)->GetPlayerShootRot() - 90)/90.0 <= 1)  Target.y = (TempTeam->GetPlayer(i)->GetPlayerShootRot() - 90)/90.0*1000.f;
                    else  Target.y = ((TempTeam->GetPlayer(i)->GetPlayerShootRot() - 270)/90.0) * -1000.f;
                    Roller->ShootTo(Target, 30);
                }
            }
        }
    }
}

sf::Vector2f Game::GetRinkPosition()
{
    mRink.getPosition();
}
