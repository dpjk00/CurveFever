#include "Player.h"

Player::Player(float radius, sf::Color color)
{
	m_Position.x = 500;
	m_Position.y = 500;

	head.setRadius(1.5f);
	head.setPosition(sf::Vector2f(m_Position.x, m_Position.y));
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

float Player::GetRotationSpeed()
{
	return m_RotationSpeed;
}

float Player::GetSize()
{
	return m_Size;
}

void Player::SetSize(float newSize)
{
	m_Size = newSize;
}

void Player::SpeedUp()
{
	m_Speed += 20.0f;
}

void Player::SetDefault(PowerUpType type)
{
	switch (type) {
	case PowerUpType::SpeedUp:
		m_Speed -= 20.0f;
		break;
	case PowerUpType::ThickLine:
		m_Size = c_Size;
		break;
	}
}
