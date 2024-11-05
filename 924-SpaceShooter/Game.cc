#include "Game.h"
#include "projectile_manager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SpaceShip.h"

Game::Game()
{
   window_.create(sf::VideoMode(1280, 720), "Space Shooter");
}

void Game::Loop()
{
    while (window_.isOpen())
    {
        sf::Event event;
        //sf::Event event_ship;
        while (window_.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window_.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                projectiles.Spawn(sf::Vector2f( event.mouseButton.x, event.mouseButton.y ));
                
            }

        }

        projectiles.Refresh(dt_, window_.getSize());
        ship_.Refresh(dt_, window_);
        window_.clear();

        window_.draw(projectiles);
        window_.draw(ship_);
        window_.display();
        dt_ = clock_.restart().asSeconds();
    }
}

