#include "Player.h"

Player::Player(float radius, sf::Color color)
{
	body.setFillColor(color);
	body.setRadius(radius);
	body.setPosition(500, 500);
	m_Position.x = 500;
	m_Position.y = 500;
}

Player::Player() = default;

Player::~Player() = default;

void Player::SetPosition(sf::Vector2f vec)
{
	m_Position = vec;
}

void Player::SetDirection(sf::Vector2f vec)
{
	m_Direction = vec;
}

sf::Vector2f Player::GetPosition()
{
	return m_Position;
}

sf::Vector2f Player::GetDirection()
{
	return m_Direction;
}

float Player::GetSpeed()
{
	return m_Speed;
}

