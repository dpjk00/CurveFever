#include "Game.h"
#include <math.h>
#include <iostream>

Game::Game()
{
	Init();
}

Game::~Game()
{
	delete m_Window;
	delete m_Player;
}

void Game::Start()
{
	MainLoop();
}

float Norm(sf::Vector2f const& v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void Game::Init()
{
	m_Window = new sf::RenderWindow(sf::VideoMode(c_WindowWidth, c_WindowWidth), "Curve Fever");
	m_Player = new Player(10, sf::Color::Red);
}

void Game::Draw()
{
	m_Window->draw(m_Player->body);
}

void Game::Movement(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_Player->SetDirection(m_Player->GetDirection() + sf::Vector2f(m_Player->GetDirection().y, -m_Player->GetDirection().x) * m_Player->GetRotationSpeed() * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_Player->SetDirection(m_Player->GetDirection() - sf::Vector2f(m_Player->GetDirection().y, -m_Player->GetDirection().x) * m_Player->GetRotationSpeed() * dt);
	}

	m_Player->SetPosition(m_Player->GetPosition() + m_Player->GetDirection() * m_Player->GetSpeed() * dt);
	m_Player->body.setPosition(m_Player->GetPosition());
}

void Game::MainLoop()
{
	sf::Clock deltaTime;
	float dt = 0.0f;
	while (m_Window->isOpen()) {
		sf::Event event;
		while (m_Window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				m_Window->close();

		m_Window->clear(sf::Color::Black);
		Movement(dt);
		Draw();
		m_Window->display();
		dt = deltaTime.restart().asSeconds();
	}
}



