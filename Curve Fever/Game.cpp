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

sf::RectangleShape shape;

void Game::Init()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_Window = new sf::RenderWindow(sf::VideoMode(c_WindowWidth, c_WindowWidth), "Curve Fever", sf::Style::Default, settings);
	m_Player = Player(10, sf::Color::Red);

	m_Player.curve = sf::VertexArray(sf::Quads);

	shape.setSize(sf::Vector2f(50, 100));
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(300, 300);
}

void Game::Draw()
{
	m_Window->draw(m_Player.head);
	m_Window->draw(m_Player.curve);
	m_Window->draw(shape);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_Player.curve.clear();
	}

	m_Player.SetPosition(m_Player.GetPosition() + m_Player.GetDirection() * m_Player.GetSpeed() * dt);
	m_Player.head.setPosition(m_Player.GetPosition() + sf::Vector2f(2, 2));
}

void Game::DrawLine()
{
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - m_Player.GetSize(), m_Player.GetPosition().y - m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + m_Player.GetSize(), m_Player.GetPosition().y - m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + m_Player.GetSize(), m_Player.GetPosition().y + m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - m_Player.GetSize(), m_Player.GetPosition().y + m_Player.GetSize())));
}

void Game::CheckCollision()
{
	if (shape.getPosition().x < m_Player.GetPosition().x + m_Player.GetSize() &&
		shape.getPosition().x + shape.getSize().x > m_Player.GetPosition().x &&
		shape.getPosition().y < m_Player.GetPosition().y + m_Player.GetSize() &&
		shape.getPosition().y + shape.getSize().y > m_Player.GetPosition().y)
		std::cout << "You hit something" << std::endl;

	// last added vertexes to array is a head
	int size = m_Player.curve.getVertexCount();
	for (int i = 0; i < size - 300; i++) {
		if (m_Player.curve[size - 3].position.x < m_Player.curve[i].position.x + m_Player.GetSize() &&
			m_Player.curve[size - 3].position.x + m_Player.head.getSize().x > m_Player.curve[i].position.x &&
			m_Player.curve[size - 3].position.y < m_Player.curve[i].position.y + m_Player.GetSize() &&
			m_Player.curve[size - 3].position.y + m_Player.head.getSize().y > m_Player.curve[i].position.y) {



			m_Player.IsAlive = false;
			if (!m_Player.IsAlive)
				break;
		}
	}
}

void Game::MainLoop()
{
	sf::Clock deltaTime;
	float dt = 0.001f;

	m_Player.SetDirection(sf::Vector2f(3, 0));

	while (m_Window->isOpen()) {
		sf::Event event;
		while (m_Window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				m_Window->close();


		m_Window->clear(sf::Color::Black);
		if (m_Player.IsAlive) {
			Movement(dt);
			DrawLine();
			CheckCollision();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			for (int i = 0; i < m_Player.curve.getVertexCount(); i++) {
				std::cout << m_Player.curve[i].position.x << " " << m_Player.curve[i].position.y << std::endl;
			}
		}
		Draw();
		m_Window->display();
		dt = deltaTime.restart().asSeconds();
	}
}



