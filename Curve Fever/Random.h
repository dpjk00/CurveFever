#pragma once

#include <random>
#include <thread>
#include <time.h>

class Random
{
public:
	static void Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	static float Int(int min, int max)
	{
		return min + (s_Distribution(s_RandomEngine) % (max - min));
	}

private:
	static std::mt19937 s_RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};

