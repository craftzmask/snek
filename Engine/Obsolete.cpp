#include "Obsolete.h"

void Obsolete::Draw(Board& brd) const
{
	brd.DrawCell(loc, c);
}

void Obsolete::Respawn(std::mt19937& rng, const Board& brd, const Snek& snek, const Food& food)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc) || newLoc == food.GetLocation());

	loc = newLoc;
}

const Location& Obsolete::GetLocation() const
{
	return loc;
}
