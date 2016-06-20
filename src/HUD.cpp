#include "HUD.h"

HUD::HUD()
{
    HUDStamina = 75.f;
    ShowHUD = true;
}

HUD::~HUD()
{
    //dtor
}

void HUD::CreatePlayerHUD(Config &config)
{
    this->config = config;
}

void HUD::ShowPlayerHUD(bool HUD)
{
    ShowHUD = HUD;
}

void HUD::Render(sf::RenderWindow &mWindow)
{
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].position = sf::Vector2f(8, 8);
    quad[1].position = sf::Vector2f(162, 8);
    quad[2].position = sf::Vector2f(162, 42);
    quad[3].position = sf::Vector2f(8, 42);
    for(int i=0; i<4; i++)quad[i].color = sf::Color::Black;
    sf::VertexArray quad2(sf::Quads, 4);
    quad2[0].position = sf::Vector2f(10, 10);
    quad2[1].position = sf::Vector2f(HUDStamina*1.5+10, 10);
    quad2[2].position = sf::Vector2f(HUDStamina*1.5+10, 40);
    quad2[3].position = sf::Vector2f(10, 40);
    for(int i=0; i<4; i++)quad2[i].color = sf::Color::Green;

    sf::Font font;
    font.loadFromFile("Media/Sansation.ttf");
    sf::Text text("Team1 vs Team2", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::Black);
    text.setPosition(400, 10);
    sf::Text result("0:0", font);
    result.setCharacterSize(30);
    result.setStyle(sf::Text::Bold);
    result.setColor(sf::Color::Black);
    result.setPosition(485, 40);
    if(ShowHUD)
    {
        mWindow.draw(quad);
        mWindow.draw(quad2);
        mWindow.draw(text);
        mWindow.draw(result);
    }
}
