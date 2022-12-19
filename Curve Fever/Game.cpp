#include "Game.h"

#define PI 3.14159265359

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

	for (int i = 0; i < m_GlobalPowerUps.size(); i++)
		m_Window->draw(m_GlobalPowerUps[i].m_Sprite);
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

	m_Player.head.setPosition(m_Player.GetPosition());
}

void Game::SpawnPowerUp()
{
	PowerUp powerUp;

	sf::CircleShape circle = sf::CircleShape();
	circle.setRadius(20);
	circle.setPosition(sf::Vector2f(Random::Int(20, c_WindowWidth - 40), Random::Int(20, c_WindowWidth)));

	Random::Init();
	int number = Random::Int(0, 2);

	switch (number)
	{
	case 0:
		// thick line
		powerUp.SetType(PowerUpType::ThickLine);
		powerUp.SetDuration(10.0f);
		circle.setFillColor(sf::Color::Cyan);
		break;
	case 1:
		// speed up
		powerUp.SetType(PowerUpType::SpeedUp);
		powerUp.SetDuration(10.0f);
		circle.setFillColor(sf::Color::Green);
		break;
	case 2:
		// can go through walls
		powerUp.SetType(PowerUpType::CanGoThroughWalls);
		circle.setFillColor(sf::Color::Magenta);
		break;
	case 3:
		// speed down
		powerUp.SetType(PowerUpType::SpeedDown);
		circle.setFillColor(sf::Color::Red);
		break;
	case 4:
		// clear map
		powerUp.SetType(PowerUpType::ClearMap);
		circle.setFillColor(sf::Color::Blue);
		break;
	}


	powerUp.m_Sprite = circle;

	m_GlobalPowerUps.push_back(powerUp);
}

void Game::DrawLine()
{
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - m_Player.GetSize(), m_Player.GetPosition().y - m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + m_Player.GetSize(), m_Player.GetPosition().y - m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x + m_Player.GetSize(), m_Player.GetPosition().y + m_Player.GetSize())));
	m_Player.curve.append(sf::Vertex(sf::Vector2f(m_Player.GetPosition().x - m_Player.GetSize(), m_Player.GetPosition().y + m_Player.GetSize())));

	// changes line to yellow
	m_Player.curve[m_Player.curve.getVertexCount() - 1].color = sf::Color::Yellow;
	m_Player.curve[m_Player.curve.getVertexCount() - 2].color = sf::Color::Yellow;
	m_Player.curve[m_Player.curve.getVertexCount() - 3].color = sf::Color::Yellow;
	m_Player.curve[m_Player.curve.getVertexCount() - 4].color = sf::Color::Yellow;

	m_Player.head.setFillColor(sf::Color::Yellow);
}

void Game::CheckCollision()
{
	int size = m_Player.curve.getVertexCount();

	// check wall collission
	if (m_Player.head.getPosition().x > c_WindowWidth || m_Player.head.getPosition().x < 0 ||
		m_Player.head.getPosition().y> c_WindowWidth || m_Player.head.getPosition().y < 0)
		m_Player.IsAlive = false;

	// check snake's collission
	for (int i = 0; i < size - 300; i++) {
		if (m_Player.head.getPosition().x < m_Player.curve[i].position.x + m_Player.GetSize() &&
			m_Player.head.getPosition().x + m_Player.GetSize() > m_Player.curve[i].position.x &&
			m_Player.head.getPosition().y < m_Player.curve[i].position.y + m_Player.GetSize() &&
			m_Player.head.getPosition().y + m_Player.GetSize() > m_Player.curve[i].position.y) {

			m_Player.IsAlive = false;
			if (!m_Player.IsAlive)
				break;
		}
	}

	// check power up collision
	for (int i = 0; i < m_GlobalPowerUps.size(); i++) {
		int dx = m_GlobalPowerUps[i].m_Sprite.getPosition().x + m_GlobalPowerUps[i].m_Sprite.getRadius() - m_Player.head.getPosition().x;
		int dy = m_GlobalPowerUps[i].m_Sprite.getPosition().y + m_GlobalPowerUps[i].m_Sprite.getRadius() - m_Player.head.getPosition().y;
		int distance = std::sqrt(dx * dx + dy * dy);

		if (distance < m_GlobalPowerUps[i].m_Sprite.getRadius() + m_Player.head.getRadius()) {
			if (m_GlobalPowerUps[i].GetType() == PowerUpType::SpeedUp) {
				m_Player.SpeedUp();
			}
			if (m_GlobalPowerUps[i].GetType() == PowerUpType::ClearMap)
				m_Player.curve.clear();
			if (m_GlobalPowerUps[i].GetType() == PowerUpType::ThickLine) {
				m_Player.SetSize(3.0f);
			}

			m_GlobalPowerUps[i].RestartDisappearance();
			m_Player.m_PowerUps.push_back(m_GlobalPowerUps[i]);
			m_GlobalPowerUps.erase(m_GlobalPowerUps.begin() + i);
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
	float dt = 0.0f;

	sf::Clock gapClock;
	sf::Clock powerUpClock;

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

			// this creates gaps in a snake
			if (gapClock.getElapsedTime().asSeconds() > 3.0f) {
				IsGapCreated = true;
				gapSize = CreateGap();
				gapClock.restart();
			}
			if (!IsGapCreated)
				DrawLine();
			if (gapClock.getElapsedTime().asSeconds() > gapSize && IsGapCreated) {
				IsGapCreated = false;
				gapClock.restart();
				gapSize = 0;
			}

			// this spawns powerups
			if (powerUpClock.getElapsedTime().asSeconds() > 5.0f) {
				SpawnPowerUp();
				powerUpClock.restart();
			}

			for (int i = 0; i < m_Player.m_PowerUps.size(); i++) {
				if (m_Player.m_PowerUps[i].GetDisappearance() > m_Player.m_PowerUps[i].GetDuration()) {
					m_Player.SetDefault(m_Player.m_PowerUps[i].GetType());
					m_Player.m_PowerUps.erase(m_Player.m_PowerUps.begin() + i);
				}
			}

			//deletes powerUps after 17 seconds
			for (int i = 0; i < m_Player.m_PowerUps.size(); i++)
				if (m_Player.m_PowerUps[i].GetDisappearance() > 17.0f)
					m_GlobalPowerUps.erase(m_Player.m_PowerUps.begin() + i);

			CheckCollision();
		}

		Draw();
		m_Window->display();
		dt = deltaTime.restart().asSeconds();
	}
}



