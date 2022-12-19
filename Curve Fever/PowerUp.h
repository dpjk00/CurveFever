#pragma once
#include <SFML/Graphics.hpp>

enum class PowerUpType
{
	ThickLine,
	SpeedUp,
	SpeedDown,
	ClearMap,
	CanGoThroughWalls
};

class PowerUp
{
public:
	PowerUp();
	~PowerUp();
	
	void SetDuration(float duration);
	float GetDuration();

	float GetDisappearance();
	void RestartDisappearance();

	void SetType(PowerUpType type);
	PowerUpType GetType();

public:
	sf::CircleShape m_Sprite;

private:
	float m_Duration;
	sf::Clock m_Disappearance;
	PowerUpType m_Type;
};

