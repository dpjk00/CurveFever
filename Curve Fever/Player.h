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

public:
	sf::CircleShape body;
	int m_RotationDir = 0;
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;

private:
	float m_Speed = 150.0f;
};

