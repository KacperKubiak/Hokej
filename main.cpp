#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Config.h"
#include "Team.h"

//#include <Box2D/Box2D.h>

int main()
{
    srand( time( NULL ) );
    Game game;
    Config config;
    sf::RenderWindow mWindow(sf::VideoMode(config.GetResolution().x, config.GetResolution().y, 32), "Game"/*, sf::Style::Fullscreen*/);
    mWindow.setFramerateLimit(60);
    game.Run(mWindow, config);
    return EXIT_SUCCESS;
}
