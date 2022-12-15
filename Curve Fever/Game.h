#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	void Start();

private:
	void MainLoop();
	void Movement(float dt);
	void Draw();
	void Init();
	void DrawLine();
	void CheckCollision();
	float CreateGap();
	void PickPowerUp();

public:
	const int c_WindowWidth = 1000;

private:
	Player m_Player;
	sf::RenderWindow* m_Window;
	bool IsGapCreated;
	std::vector<float> m_Gaps;
	std::vector<sf::CircleShape> m_PowerUps;
};

