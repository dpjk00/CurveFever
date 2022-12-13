#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Player
{
public:
	Player(float radius, sf::Color color);
	Player();
	~Player();
	void SetPosition(sf::Vector2f vec);
	void SetDirection(sf::Vector2f vec);
	sf::Vector2f GetPosition();
	sf::Vector2f GetDirection();
	float GetSpeed();
	float GetRotationSpeed();
	float GetSize();

public:
	sf::VertexArray curve;
	sf::RectangleShape head;
	bool IsAlive = true;

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	float m_Speed = 50.0f;
	float m_RotationSpeed = 4.0f;
	float m_Size = 1;
};

