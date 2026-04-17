#include "Food.h"

Food::Food(std::mt19937& rng, const Board& brd, const Snek& snek)
{
	Respawn(rng, brd, snek);
}

void Food::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Food::Respawn(std::mt19937& rng, const Board& brd, const Snek& snek)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);
	
	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc));

	loc = newLoc;
}

const Location& Food::GetLocation() const
{
	return loc;
}
