#pragma once

#include <random>

#include "Prologue.h"

class Random
{
public:
	static void Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	static std::pair<uint, uint> RandomPos(std::pair<uint, uint> range)
	{
		return {s_Distribution(s_RandomEngine) % range.first, s_Distribution(s_RandomEngine) % range.second};
	}

	static uint RandomUint(uint range)
	{
		return s_Distribution(s_RandomEngine) % range;
	}
	
private:
	static std::mt19937 s_RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};
