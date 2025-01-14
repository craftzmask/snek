#include "Rock.h"

void Rock::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Rock::Init(std::mt19937& rng, const Board& brd, const Snek& snek)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location newLoc;
	do
	{
		newLoc = { xDist(rng), yDist(rng) };
	} while (snek.IsInTile(newLoc));

	loc = newLoc;
}

const Location& Rock::GetLocation() const
{
	return loc;
}
