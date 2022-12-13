#include "Game.h"
#include <math.h>
#include <iostream>
#include "Random.h"

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

	m_Gaps = std::vector<float> {0.0f, 0.15f, 0.3f};
}

void Game::Draw()
{
	m_Window->draw(m_Player.curve);
	m_Window->draw(m_Player.head);

	// TODO: delete snake's acceleration when it takes a turn
	// TODO: function that creates gaps in a snake
	// TODO: implement class PowerUP
	// TODO: create AI
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

	m_Player.head.setPosition(m_Player.GetPosition());
}

void Game::DrawLine()
{
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - m_Player.GetSize(), m_Player.GetPosition().y - m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + m_Player.GetSize(), m_Player.GetPosition().y - m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + m_Player.GetSize(), m_Player.GetPosition().y + m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - m_Player.GetSize(), m_Player.GetPosition().y + m_Player.GetSize())));

	m_Player.curve[m_Player.curve.getVertexCount() / 4].color = sf::Color::Yellow;
}

void Game::CheckCollision()
{
	// last added vertexes to array is a head
	int size = m_Player.curve.getVertexCount();
	for (int i = 0; i < size - 300; i++) {
		if (m_Player.curve[size - 3].position.x < m_Player.curve[i].position.x + m_Player.GetSize() &&
			m_Player.curve[size - 3].position.x + m_Player.GetSize() > m_Player.curve[i].position.x &&
			m_Player.curve[size - 3].position.y < m_Player.curve[i].position.y + m_Player.GetSize() &&
			m_Player.curve[size - 3].position.y + m_Player.GetSize() > m_Player.curve[i].position.y) {

			m_Player.IsAlive = false;
			if (!m_Player.IsAlive)
				break;
		}
	}
}

float Game::CreateGap()
{
	// 0.3s = big gap
	// 0.15s = small gap
	// 0 = no gap

	return m_Gaps[Random::Int(0, m_Gaps.size())];
}

void Game::MainLoop()
{
	sf::Clock deltaTime;
	float dt = 0.001f;

	sf::Clock clock;

	m_Player.SetDirection(sf::Vector2f(3, 0));

	float gapSize = 0;

	while (m_Window->isOpen()) {
		sf::Event event;
		while (m_Window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				m_Window->close();

		m_Window->clear(sf::Color::Black);
		if (m_Player.IsAlive) {
			Movement(dt);
			if (clock.getElapsedTime().asSeconds() > 3.0f) {
				IsGapCreated = true;
				gapSize = CreateGap();
				std::cout << gapSize << std::endl;
				clock.restart();
			}
			if (!IsGapCreated)
				DrawLine();
			CheckCollision();

			if (clock.getElapsedTime().asSeconds() > gapSize && IsGapCreated) {
				IsGapCreated = false;
				clock.restart();
				gapSize = 0;
			}
		}
		Draw();
		m_Window->display();
		dt = deltaTime.restart().asSeconds();
	}
}



