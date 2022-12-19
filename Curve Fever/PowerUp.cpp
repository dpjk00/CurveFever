#include "PowerUp.h"

PowerUp::PowerUp() = default;
PowerUp::~PowerUp() = default;

void PowerUp::SetDuration(float duration)
{
	m_Duration = duration;
}

void PowerUp::SetType(PowerUpType type)
{
	m_Type = type;
}

float PowerUp::GetDuration()
{
	return m_Duration;
}

PowerUpType PowerUp::GetType()
{
	return m_Type;
}

float PowerUp::GetDisappearance()
{
	return m_Disappearance.getElapsedTime().asSeconds();
}

void PowerUp::RestartDisappearance()
{
	m_Disappearance.restart();
}