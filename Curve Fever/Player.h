#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "PowerUp.h"

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
	void SetSize(float newSize);
	void SpeedUp();
	void SetDefault(PowerUpType type);

public:
	sf::VertexArray curve;
	sf::CircleShape head;
	bool IsAlive = true;
	bool isThickLine = false;
	std::vector<PowerUp> m_PowerUps;

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;

	float m_Speed = 50.0f;
	float m_RotationSpeed = 4.0f;
	float m_Size = 1;
	
	float c_Size = 1;

};

