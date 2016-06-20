#include "roller.h"

roller::roller()
{
    VirtualPos.x = 0.f;
    VirtualPos.y = 0.f;
    IsAttached = false;
}

roller::~roller()
{
    //dtor
}

void roller::AddRoller(Config &config)
{
    if (rTexture.loadFromFile("Media/Textures/roller.png"))
	{
        sRoller.setTexture(rTexture);
        float centerx, centery;
        centerx = (config.GetResolution().x-rTexture.getSize().x)/2;
        centery = (config.GetResolution().y-rTexture.getSize().y)/2;
        sRoller.setPosition(centerx, centery);
        sRoller.scale(0.15f, 0.15f);
	}
	else
    {
        std::cout << "Error: Can't load texture" << std::endl;
    }
}

void roller::Render(sf::RenderWindow &mWindow)
{
    mWindow.draw(sRoller);
}

void roller::Update(sf::Time elapsedTime, sf::Sprite &mRink)
{
    sf::Vector2f pos = sRoller.getPosition();
    sf::Vector2u tsize = sRoller.getTexture()->getSize();
    sf::Vector2f rpos = mRink.getPosition();
    sf::Vector2u rsize = mRink.getTexture()->getSize();
    sf::Vector2f PlayerMovement(0.f, 0.f);
    sRoller.setPosition(rsize.x/2 + rpos.x - (rTexture.getSize().x * 0.15f)/2, rsize.y/2 + rpos.y - (rTexture.getSize().y * 0.15f)/2);
    pos = sRoller.getPosition();
    if(IsAttached)
    {
        PlayerMovement = AttachToPlayer->GetVirtualPlayerPos();
        PlayerMovement.x += 2000.f;
        PlayerMovement.y += 1500.f;
        sRoller.move((PlayerMovement) * elapsedTime.asSeconds());
        VirtualPos = PlayerMovement;
        //std::cout << VirtualPos.x/30 << " " << VirtualPos.y/30 << std::endl;
        //1080
        //2360
    }
    else
    {
        if(shotlong > 0)
        {
            shotlong--;
            if(VirtualPos.x + ShotTarget.x >= -1080.f*30 && VirtualPos.x + ShotTarget.x <= 1080.f*30)VirtualPos.x += ShotTarget.x;
            if(VirtualPos.y + ShotTarget.y >= -2360.f*30 && VirtualPos.y + ShotTarget.y <= 2360.f*30)VirtualPos.y += ShotTarget.y;
        }
        sRoller.move(VirtualPos * elapsedTime.asSeconds());
    }
}

sf::Vector2f roller::GetRollerPos()
{
    return sRoller.getPosition();
}

sf::Vector2f roller::GetVirtualRollerPos(sf::Sprite &mRink)
{
    return VirtualPos;
}

void roller::AttachRollerToPlayer(bool attach, Player* Players)
{
    AttachToPlayer = Players;
    IsAttached = attach;
}

void roller::ShootTo(sf::Vector2f Target, int slong)
{
    shotlong = slong;
    ShotTarget = Target;
    /*VirtualPos += Target;
    ShotTarget.x = VirtualPos.x + (Target.x * slong);
    ShotTarget.y = VirtualPos.y + (Target.y * slong);*/
}
