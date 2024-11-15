#include "Game.h"

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

constexpr float kCooldown_limit = 0.15f;

Game::Game()
{
	window_.create(sf::VideoMode(1280, 720), "Space Shooter");
	backgroundTexture.loadFromFile("assets\\bg5.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	// Charger le fichier audio dans un buffer
	buffer.loadFromFile("assets\\Bonus\\laser5.wav");
	// Associer le buffer à un objet Sound
	sound.setBuffer(buffer);
	font.loadFromFile("assets\\minecraft\\Minecraft.ttf");
	text_game_over.setFont(font);
	text_hp.setFont(font);
	text_score.setFont(font);
	background_music.openFromFile("assets\\Zapper101_s-VGM-Fun-_93_-No-More-Heroes-2-Dose-of-Innocence.wav");
	background_music.setLoop(true);
	background_music.play();
	game_over_music.openFromFile("assets\\Rick-Roll-Sound-Effect.wav");
}

void Game::Loop()
{
	window_.setMouseCursorVisible(false);

	double dt = 0.036f;
	double cooldown_shoot = 0;


	while (window_.isOpen())
	{
		text_hp.setString("HP : " + std::to_string(ship_.GetHp()));
		text_hp.setOrigin(text_hp.getGlobalBounds().width , 0);
		text_hp.setPosition(window_.getSize().x-10, 10);

		text_score.setString("Score : " + std::to_string(score));
		text_score.setOrigin(0, text_score.getGlobalBounds().height);
		text_score.setPosition(10, window_.getSize().y - 10);


		cooldown_shoot += dt;

		if (!ship_.GetStarshipIsDead())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (cooldown_shoot >= kCooldown_limit)
				{
					projectiles.Spawn(ship_.GetPosition(), { 1500,0 });
					ship_.ShootConfirm();
					// Jouer le son
					sound.play();
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
		}




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

		if (!ship_.GetStarshipIsDead())
		{
			projectiles.Refresh(dt, window_.getSize());
			asteroid_.Refresh(dt, window_.getSize());

			enemy_projectiles.Refresh(dt, window_.getSize());
			enemy_manager.Refresh(dt, window_.getSize(), enemy_projectiles);
			if (!ship_.GetHit())
			{
				ship_.CheckCollisions(asteroid_.GetEntities());
				ship_.CheckCollisions(enemy_manager.GetEntities());
				ship_.CheckCollisions(enemy_projectiles.GetEntities());
			}
			else
			{
				hit_cooldown += dt;
				ship_.Hit(hit_cooldown);
			}

			projectiles.CheckCollisions(asteroid_.GetEntities(), score);
			projectiles.CheckCollisions(enemy_manager.GetEntities(), score);
		}


		window_.clear();
		// Dessiner l'arrière-plan
		window_.draw(backgroundSprite);
		if (!ship_.GetStarshipIsDead())
		{
			window_.draw(projectiles);
			window_.draw(enemy_projectiles);
			window_.draw(asteroid_);
			window_.draw(enemy_manager);
			window_.draw(ship_);
			window_.draw(text_hp);
			window_.draw(text_score);
		}
		else
		{
			background_music.stop();

			if (game_over_music.getStatus() == sf::Music::Stopped)
			{
				game_over_music.play();
			}

			if (game_over_music.getStatus() == sf::Music::Playing)
			{
				game_over_cooldown_ += dt;
			}

			if (game_over_cooldown_ >= game_over_music.getDuration().asSeconds())
			{
				window_.close();
			}

			text_game_over.setString("Game Over \n You Score : " + std::to_string(score));
			text_game_over.setOrigin(text_game_over.getGlobalBounds().width/2,text_game_over.getGlobalBounds().height/2);
			text_game_over.setPosition(window_.getSize().x / 2, window_.getSize().y / 2);
			window_.draw(text_game_over);
		}
		window_.display();


		// At the end of the game loop
		dt = clock_.restart().asSeconds();
		//std::cout << "dt ? : " << dt << std::endl;
	}
	window_.setMouseCursorVisible(true);
}

void Game::SoundLaserEnd()
{
	// Jouer le son
	sound.play();
	// Attendre que le son soit terminé (optionnel)
	while (sound.getStatus() == sf::Sound::Playing) {
		sf::sleep(sf::milliseconds(100)); // Eviter de consommer 100% du CPU
	}
}

