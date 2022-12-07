#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	void Start();
	void MainLoop();
	void Movement(float dt);
	void Draw();
	void Init();
	void DrawLine();
	void CheckCollision();

public:
	const int c_WindowWidth = 1000;

private:
	Player m_Player;
	sf::RenderWindow* m_Window;
};

