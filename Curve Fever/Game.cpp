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

float Norm(sf::Vector2f& v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void Game::Movement(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_Player->m_Direction += sf::Vector2f(m_Player->m_Direction.y, -m_Player->m_Direction.x) * 5.0f * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_Player->m_Direction -= sf::Vector2f(m_Player->m_Direction.y, -m_Player->m_Direction.x) * 5.0f * dt;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_Player->SetDirection(sf::Vector2f(1, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_Player->SetDirection(sf::Vector2f(-1, 0));
	}

	m_Player->m_Position += m_Player->m_Direction * m_Player->GetSpeed() * dt;
	m_Player->body.setPosition(m_Player->m_Position);
}

void Game::MainLoop()
{
	sf::Clock deltaTime;
	float dt = 0.0001f;
	while (m_Window->isOpen()) {
		sf::Event event;
		while (m_Window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				m_Window->close();

		m_Window->clear(sf::Color::Black);
		Movement(dt);
		Draw();
		m_Window->display();
		//m_Window->setFramerateLimit(30);
		dt = deltaTime.restart().asSeconds();
	}
}



