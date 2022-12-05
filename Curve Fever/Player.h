#pragma once
#include <SFML/Graphics.hpp>

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

public:
	sf::CircleShape body;

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;
	float m_Speed = 200.0f;
	float m_RotationSpeed = 5.0f;
};

