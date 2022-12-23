#include "Player.h"

Player::Player(float radius, sf::Color color)
{
	m_Position.x = 490;
	m_Position.y = 490;

	head.setRadius(1.5f);
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
	m_Speed = 80.0f;
}

void Player::SpeedDown()
{
	m_Speed = 40.0f;
}

void Player::GoThroughWalls()
{
	if (m_Position.x < 0) {
		m_Position.x = 1000;
	}
	if (m_Position.y < 0) {
		m_Position.y = 1000;
	}
	if (m_Position.x > 1000) {
		m_Position.x = 0;
	}
	if (m_Position.y > 1000) {
		m_Position.y = 0;
	}
}

void Player::SetDefault(PowerUpType type)
{
	switch (type) {
	case PowerUpType::SpeedUp:
		m_Speed = m_BaseSpeed;
		isSpeedUp = false;
		break;
	case PowerUpType::ThickLine:
		m_Size = m_BaseSize;
		isThickLine = false;
		break;
	case PowerUpType::SpeedDown:
		m_Speed = m_BaseSpeed;
		isSpeedDown = false;
		break;
	case PowerUpType::CanGoThroughWalls:
		canGoThroughWalls = false;
		break;
	}
}

void Player::SetDefault()
{
	m_Speed = m_BaseSpeed;
	isSpeedUp = false;

	m_Size = m_BaseSize;
	isThickLine = false;

	m_Speed = m_BaseSpeed;
	isSpeedDown = false;

	canGoThroughWalls = false;
}
