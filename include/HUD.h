#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Config.h"
#include <iostream>
#include <vector>
#include <string>

class HUD
{
    public:
        HUD();
        virtual ~HUD();
        void ShowPlayerHUD(bool HUD);
        void Render(sf::RenderWindow &mWindow);
        void CreatePlayerHUD(Config &config);
        void UpdatePlayerHUD(float stamina);
    protected:
    private:
        Config config;
        bool ShowHUD;
        float HUDStamina;
};

#endif // HUD_H
