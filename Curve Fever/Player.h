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
	void SpeedDown();
	void GoThroughWalls();
	void SetDefault(PowerUpType type);
	void SetDefault();

public:
	sf::VertexArray curve;
	sf::CircleShape head;

	bool IsAlive = true;
	std::vector<PowerUp> m_PowerUps;

	bool isThickLine = false;
	bool isSpeedUp = false;
	bool isSpeedDown = false;
	bool canGoThroughWalls = false;

private:
	sf::Vector2f m_Position;
	sf::Vector2f m_Direction;

	float m_Speed = 60.0f;
	float m_RotationSpeed = 4.0f;
	float m_Size = 1;
	
	float m_BaseSize = 1;
	float m_BaseSpeed = 60.0f;

};

