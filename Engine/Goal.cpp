#include "Goal.h"
#include <random>

Goal::Goal(const Location& loc, Color c)
	:
	loc(loc),
	c(c)
{
}

void Goal::Draw(Board& brd) const
{
	brd.Draw(loc, c);
}

void Goal::Respawn(const Board& brd, const Snek& snek)
{	
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetGridHeight() - 1);
	
	Location new_loc;
	do
	{
		new_loc = { xDist(rng), yDist(rng) };
	} while (snek.IsInTile(new_loc));

	loc = new_loc;
}

bool Goal::TestCollision(const Location& other) const
{
	return loc.x == other.x && loc.y == other.y;
}
