#pragma once
#include "Location.h"
#include "Board.h"
#include "Snek.h"
#include "Food.h"
#include <random>

class Obsolete
{
public:
	void Draw(Board& brd) const;
	void Respawn(std::mt19937& rng, const Board& brd, const Snek& snek, const Food& food);
	const Location& GetLocation() const;
private:
	Location loc = { 0, 0 };
	Color c = Colors::Gray;
};