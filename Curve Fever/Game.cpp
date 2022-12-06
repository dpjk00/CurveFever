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
}

void Game::Start()
{
	MainLoop();
}

void Game::Init()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_Window = new sf::RenderWindow(sf::VideoMode(c_WindowWidth, c_WindowWidth), "Curve Fever", sf::Style::Default, settings);
	m_Player = Player(10, sf::Color::Red);

	m_Player.curve = sf::VertexArray(sf::Quads);
}

void Game::Draw()
{
	m_Window->draw(m_Player.curve);
}

void Game::Movement(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_Player.SetDirection(m_Player.GetDirection() + sf::Vector2f(m_Player.GetDirection().y, -m_Player.GetDirection().x) * m_Player.GetRotationSpeed() * dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_Player.SetDirection(m_Player.GetDirection() - sf::Vector2f(m_Player.GetDirection().y, -m_Player.GetDirection().x) * m_Player.GetRotationSpeed() * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_Player.SetDirection(sf::Vector2f(3, 0));
	}

	m_Player.SetPosition(m_Player.GetPosition() + m_Player.GetDirection() * m_Player.GetSpeed() * dt);
	m_Player.body.setPosition(m_Player.GetPosition());
}

void Game::DrawLine()
{
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - 5, m_Player.GetPosition().y - 5)));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + 5, m_Player.GetPosition().y - 5)));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + 5, m_Player.GetPosition().y + 5)));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - 5, m_Player.GetPosition().y + 5)));
	std::cout << m_Player.curve.getVertexCount() << std::endl;
}

void Game::MainLoop()
{
	sf::Clock deltaTime;
	float dt = 0.0f;
	int eachTime = 0;

	while (m_Window->isOpen()) {
		sf::Event event;
		while (m_Window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				m_Window->close();

		m_Window->clear(sf::Color::Black);
		Movement(dt);
		if (eachTime == 8) {
			DrawLine();
			eachTime = 0;
		}
		Draw();
		m_Window->display();
		dt = deltaTime.restart().asSeconds();
		eachTime++;
	}
}



