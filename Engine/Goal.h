#pragma once

#include "Graphics.h"
#include "Location.h"
#include "Board.h"
#include "Snek.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snek& snek);
	void Draw(Board& brd) const;
	void Respawn(std::mt19937& rng, const Board& brd, const Snek& snek);
	const Location& GetLocation() const;
private:
	Location loc;
	Color c = Colors::Red;
};