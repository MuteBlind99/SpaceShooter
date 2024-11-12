#include "Game.h"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

constexpr float kCooldown_limit = 0.15f;

Game::Game()
{
	window_.create(sf::VideoMode(1280, 720), "Space Shooter");
}

void Game::Loop()
{
	window_.setMouseCursorVisible(false);

	double dt = 0.016f;
	double cooldown_shoot = 0;


	while (window_.isOpen())
	{
		cooldown_shoot += dt;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (cooldown_shoot >= kCooldown_limit)
			{
				projectiles.Spawn(ship_.GetPosition(), { 1500,0 });
				ship_.ShootConfirm();
				cooldown_shoot = 0;
			}


		}
		// what's the current position of the X and Y axes of joystick number 0?
		const float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		const float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

		if (x * x + y * y > 0)
			ship_.Move({ x / 100.0f , y / 100.0f }, dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			ship_.Move({ 0, -1 }, dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			ship_.Move({ 0, 1 }, dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			ship_.Move({ -1 , 0 }, dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			ship_.Move({ 1, 0 }, dt);




		sf::Event event;
		//sf::Event event_ship;

		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_.close();

			/*if (event.type == sf::Event::MouseMoved)
			{
				ship_.SetPositon(sf::Vector2u(event.mouseMove.x, event.mouseMove.y));

			}*/

			if (event.type == sf::Event::JoystickButtonReleased)
			{
				std::cout << "Button ID #" << event.joystickButton.button << '\n';
			}

			if (event.type == sf::Event::JoystickMoved)
			{
				std::cout << "Axis ID" << event.joystickMove.axis << '\n';
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					// Fullscreen <=> not fullscreen
					window_.close();
				}
			}

		}

		projectiles.Refresh(dt, window_.getSize());
		asteroid_.Refresh(dt, window_.getSize());

		enemy_projectiles.Refresh(dt, window_.getSize());
		enemy_manager.Refresh(dt, window_.getSize(), enemy_projectiles);

		ship_.CheckCollisions(asteroid_.GetEntities());
		ship_.CheckCollisions(enemy_manager.GetEntities());
		ship_.CheckCollisions(enemy_projectiles.GetEntities());

		projectiles.CheckCollisions(asteroid_.GetEntities());
		projectiles.CheckCollisions(enemy_manager.GetEntities());


		window_.clear();

		window_.draw(projectiles);
		window_.draw(enemy_projectiles);
		window_.draw(asteroid_);
		window_.draw(enemy_manager);
		window_.draw(ship_);
		window_.display();


		// At the end of the game loop
		dt = clock_.restart().asSeconds();
		//std::cout << "dt ? : " << dt << std::endl;
	}
	window_.setMouseCursorVisible(true);
}

