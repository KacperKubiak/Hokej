#include "Player.h"

Player::Player()
{
    for(int i=0; i<6; i++)
    {
        pName += rand()%25+65;
    }
    std::cout << pName << std::endl;
}

void Player::AddPlayer(bool isbot, Config &config, sf::Texture &pTexture, string kit)
{
    ShotRot = 0.f;
    RealPos.x = 0.f;
    RealPos.y = 0.f;
    VirutalPos.x = 0.f;
    VirutalPos.y = 0.f;
    stamina = 100.f;
    power = rand()%50+50;
    std::cout << power << std::endl;
    pAI = isbot;
    pIsMovingUp = pIsMovingDown = pIsMovingRight = pIsMovingLeft = pIsMovingSprint = pIsMovingShoot = false;
    pIsHoldingBall = false;

    if (pTexture.loadFromFile(kit))
	{
        pPlayer.setTexture(pTexture);
        float centerx, centery;
        centerx = (config.GetResolution().x-pTexture.getSize().x)/2;
        centery = (config.GetResolution().y-pTexture.getSize().y)/2;
        pPlayer.setPosition(centerx, centery);
        if(isbot)
        {
            VirutalPos.x += rand()%400*100-800*100;
            VirutalPos.y += rand()%400*100-800*100;
        }
	}
	else
    {
        std::cout << "Error: Can't load texture" << std::endl;
    }
    this->pTexture = pTexture;

    if (aTexture.loadFromFile("Media/Textures/arrow.png"))
	{
        aSprite.setTexture(aTexture);
        float centerx, centery;
        centerx = (config.GetResolution().x-aTexture.getSize().x)/2;
        centery = (config.GetResolution().y-aTexture.getSize().y - 100.0)/2;
        aSprite.setPosition(centerx, centery);
        //aSprite.scale(0.15f, 0.15f);
        aSprite.setRotation(0.0);
	}
	else
    {
        std::cout << "Error: Can't load texture" << std::endl;
    }
}

Player::~Player()
{
}

void Player::OnPlayerKeyStateChange(sf::Keyboard::Key key, bool isPressed)
{
    if(!pAI)
    {
        if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
            pIsMovingUp = isPressed;
        else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
            pIsMovingDown = isPressed;
        else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
            pIsMovingLeft = isPressed;
        else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
            pIsMovingRight = isPressed;
        else if (key == sf::Keyboard::LShift)
            pIsMovingSprint = isPressed;
        else if (key == sf::Keyboard::Space)
            pIsMovingShoot = isPressed;
    }
}

void Player::OnPlayerUpdate(sf::Time elapsedTime, sf::Sprite &mRink, float PlayerSpeed)
{
	if(!pAI)
    {
        /*
        if(left)VirutalPos.x -= PlayerSpeed * sprint;//PlayerMovement.x += VirutalPos.x;
        if(up)VirutalPos.y -= PlayerSpeed * sprint;//PlayerMovement.y += VirutalPos.y;
        if(right)VirutalPos.x += PlayerSpeed * sprint;//PlayerMovement.x += VirutalPos.x;
        if(down)VirutalPos.y += PlayerSpeed * sprint;//PlayerMovement.y += VirutalPos.y;
        PlayerMovement.x += VirutalPos.x;
        PlayerMovement.y += VirutalPos.y;
        */
        sf::Vector2f pos = pPlayer.getPosition();
        sf::Vector2u tsize = pPlayer.getTexture()->getSize();
        sf::Vector2f PlayerMovement(0.f, 0.f);
        sf::Vector2f RinkMovement(0.f, 0.f);
        sf::Vector2f rpos = mRink.getPosition();
        sf::Vector2u rsize = mRink.getTexture()->getSize();

        float sprint = 1;
        if(pIsMovingSprint) sprint = 4.f;

        if(pIsMovingLeft)
        {
            if(rpos.x < 0.f && (pos.x <= (config.GetResolution().x-tsize.x)/2))
            {
                VirutalPos.x -= PlayerSpeed * sprint;
                RinkMovement.x -= PlayerSpeed;
            }
            else if(pos.x > 0.f)
            {
                VirutalPos.x -= PlayerSpeed * sprint;
                PlayerMovement.x -= PlayerSpeed;
            }
        }
        if(pIsMovingRight)
        {
            if(-rpos.x < rsize.x-config.GetResolution().x && (pos.x >= (config.GetResolution().x-tsize.x)/2))
            {
                RinkMovement.x += PlayerSpeed;
                VirutalPos.x += PlayerSpeed * sprint;
            }
            else if(pos.x < config.GetResolution().x-tsize.x)
            {
                PlayerMovement.x += PlayerSpeed;
                VirutalPos.x += PlayerSpeed * sprint;
            }
        }
        if(pIsMovingUp)
        {
            if(rpos.y < 0.f && (pos.y <= (config.GetResolution().y-tsize.y)/2))
            {
                RinkMovement.y -= PlayerSpeed;
                VirutalPos.y -= PlayerSpeed * sprint;
            }
            else if(pos.y > 0.f)
            {
                PlayerMovement.y -= PlayerSpeed;
                VirutalPos.y -= PlayerSpeed * sprint;
            }
        }
        if(pIsMovingDown)
        {
            if(-rpos.y < rsize.y-config.GetResolution().y && (pos.y >= (config.GetResolution().y-tsize.y)/2))
            {
                RinkMovement.y += PlayerSpeed;
                VirutalPos.y += PlayerSpeed * sprint;
            }
            else if(pos.y < config.GetResolution().y-tsize.y)
            {
                PlayerMovement.y += PlayerSpeed;
                VirutalPos.y += PlayerSpeed * sprint;
            }
        }
        if(pIsMovingShoot)
        {
            if(pIsHoldingBall)
            {
                std::cout << "STRZAŁ!" << std::endl;

            }
        }
        if(pIsMovingDown)
        {
            aSprite.setRotation(180.0);
            if(pIsMovingLeft) aSprite.rotate(45.0);
            if(pIsMovingRight) aSprite.rotate(-45.0);
        }
        if(pIsMovingUp)
        {
            aSprite.setRotation(0.0);
            if(pIsMovingLeft) aSprite.rotate(-45.0);
            if(pIsMovingRight) aSprite.rotate(45.0);
        }
        if(pIsMovingLeft && !pIsMovingUp && !pIsMovingDown) aSprite.setRotation(270.0);
        if(pIsMovingRight && !pIsMovingUp && !pIsMovingDown) aSprite.setRotation(90.0);
        if(pIsMovingLeft && pIsMovingDown && !pIsMovingUp && !pIsMovingDown) aSprite.setRotation(0.0);
        ShotRot = aSprite.getRotation();
        pPlayer.move(PlayerMovement * sprint * elapsedTime.asSeconds());
        aSprite.move(PlayerMovement * sprint * elapsedTime.asSeconds());
        mRink.move(-RinkMovement * sprint * elapsedTime.asSeconds());
    }
    else
    {
        sf::Vector2f pos = pPlayer.getPosition();
        sf::Vector2u tsize = pPlayer.getTexture()->getSize();
        sf::Vector2f PlayerMovement(0.f, 0.f);
        sf::Vector2f RinkMovement(0.f, 0.f);
        sf::Vector2f rpos = mRink.getPosition();
        sf::Vector2u rsize = mRink.getTexture()->getSize();

        float sprint = 1;
        if(pIsMovingSprint) sprint = 4.f;
        pPlayer.setPosition(rsize.x/2 + rpos.x - pTexture.getSize().x/2, rsize.y/2 + rpos.y - pTexture.getSize().y/2);
        //VirutalPos.x += PlayerSpeed;
        //VirutalPos.y += PlayerSpeed;
        /*PlayerMovement.x += VirutalPos.x;
        PlayerMovement.y += VirutalPos.y;
        pPlayer.move(PlayerMovement * sprint * elapsedTime.asSeconds());*/
    }
}

void Player::Render(sf::RenderWindow &mWindow)
{
    mWindow.draw(pPlayer);
    if(!pAI)
    {
        mWindow.draw(aSprite);
        pHud.Render(mWindow);
    }
}

sf::Vector2f Player::GetPlayerPos()
{
    if(pAI) return VirutalPos;
    return pPlayer.getPosition();
}

sf::Vector2f Player::GetVirtualPlayerPos()
{
    return VirutalPos;
}

sf::Vector2u Player::GetPlayerSize()
{
    return pPlayer.getTexture()->getSize();
}

bool Player::IsPlayerBot()
{
    return pAI;
}

void Player::SetPlayerBot(bool bot)
{
    pAI = bot;
}

void Player::AIMove(bool left, bool up, bool right, bool down, bool issprint, sf::Time elapsedTime, float PlayerSpeed)
{
    if(pAI)
    {
        float sprint = 1;
        if(issprint) sprint = 4.f;
        sf::Vector2f PlayerMovement(0.f, 0.f);
        if(left)VirutalPos.x -= PlayerSpeed * sprint;//PlayerMovement.x += VirutalPos.x;
        if(up)VirutalPos.y -= PlayerSpeed * sprint;//PlayerMovement.y += VirutalPos.y;
        if(right)VirutalPos.x += PlayerSpeed * sprint;//PlayerMovement.x += VirutalPos.x;
        if(down)VirutalPos.y += PlayerSpeed * sprint;//PlayerMovement.y += VirutalPos.y;
        PlayerMovement.x += VirutalPos.x;
        PlayerMovement.y += VirutalPos.y;
        pPlayer.move(PlayerMovement * elapsedTime.asSeconds());
    }
}

std::string Player::GetPlayerName()
{
    return pName;
}

bool Player::GetPlayerHoldingBall()
{
    return pIsHoldingBall;
}

void Player::SetPlayerHoldingBall(bool holding)
{
    pIsHoldingBall = holding;
}

bool Player::IsPlayerShoot()
{
    return pIsMovingShoot;
}

float Player::GetPlayerShootRot()
{
    return ShotRot;
}
